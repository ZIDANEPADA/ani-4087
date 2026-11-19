// Exercice 10 - La projection a la main
// Calcul au demarrage, avant la fenetre : 10 lignes a l'ecran et dans ecarts.txt.

#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

#include "NKEvent/NkEventSystem.h"

#include "NKLogger/NkLog.h"

#include "NKTime/NkClock.h"

#include "NKRHI/Core/NkDeviceFactory.h"
#include "NKRHI/Core/NkGraphicsApi.h"

#include "NKRenderer/NkRenderer.h"
#include "NKRenderer/Core/NkCamera.h"
#include "NKRenderer/Core/NkRenderGraph.h"
#include "NKRenderer/Materials/NkMaterialCollection.h"
#include "NKRenderer/Mesh/NkMeshSystem.h"
#include "NKRenderer/Tools/Offscreen/NkOffscreenTarget.h"
#include "NKRenderer/Tools/Render2D/NkRender2D.h"
#include "NKRenderer/Tools/Render3D/NkRender3D.h"

#include "NKImage/Core/NkImage.h"
#include "NKMath/NkQuat.h"
#include "NKMath/NkMat.h"
#include "NKMath/NkAngle.h"
#include "NKTime/NkChrono.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKWindow/Core/NkWindow.h"
#include <cstdarg>

#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace nkentseu;
using namespace nkentseu::renderer;

namespace {

    // ── Les dimensions de la salle, en un seul endroit ────────────────────
    const float32 kPiece = 4.00f;       // côté intérieur du sol
    const float32 kPlafond = 2.50f;     // hauteur sous plafond
    const float32 kMur = 0.10f;         // épaisseur d'un mur
    const float32 kPorteL = 0.90f;      // porte : largeur
    const float32 kPorteH = 2.00f;      //         hauteur
    const float32 kFenL = 1.20f;        // fenêtre : largeur
    const float32 kFenH = 1.00f;        //           hauteur
    const float32 kFenY = 1.40f;        //           hauteur de son centre
    const float32 kTableL = 1.20f;      // table : longueur
    const float32 kTableP = 0.80f;      //         profondeur
    const float32 kTableH = 0.75f;      //         hauteur du plateau
    const float32 kYeux = 1.70f;        // hauteur des yeux, debout

    const float32 kDemi = kPiece * 0.5f;

    // ── Petits outils pour piloter la salle depuis le terminal ────────────
    // Ils servent à prendre les captures SANS toucher au code :
    //   MASALLE_SHOT=120           capture l'image numéro 120, puis quitte
    //   MASALLE_SHOT_PATH=x.png    nom du fichier de capture
    //   MASALLE_CAM="x,y,z"        position de la caméra
    //   MASALLE_TARGET="x,y,z"     point regardé
    int EnvInt(const char *nom, int defaut) {
        const char *v = std::getenv(nom);
        return v ? std::atoi(v) : defaut;
    }
    const char *EnvStr(const char *nom, const char *defaut) {
        const char *v = std::getenv(nom);
        return (v && v[0]) ? v : defaut;
    }
    bool EnvVec3(const char *nom, NkVec3f &out) {
        const char *v = std::getenv(nom);
        if (!v) return false;
        float x, y, z;
        if (std::sscanf(v, "%f,%f,%f", &x, &y, &z) != 3) return false;
        out = { x, y, z };
        return true;
    }

    // Un pavé posé dans la salle. `centre` est le centre géométrique, `taille`
    // les trois dimensions en mètres.
    void Pave(NkRender3D *r3d, NkMeshSystem *meshes, const NkVec3f &centre,
              const NkVec3f &taille, const NkVec3f &teinte, float32 rugosite = 1.f) {
        NkDrawCall3D dc;
        dc.mesh = meshes->GetCube();
        dc.transform = NkMat4f::Translate(centre) * NkMat4f::Scale(taille);
        dc.aabb = { { centre.x - taille.x * 0.5f, centre.y - taille.y * 0.5f,
                      centre.z - taille.z * 0.5f },
                    { centre.x + taille.x * 0.5f, centre.y + taille.y * 0.5f,
                      centre.z + taille.z * 0.5f } };
        dc.tint = teinte;
        dc.metallic = 0.f;
        dc.roughness = rugosite;
        r3d->Submit(dc);
    }

    void SoumettreLaSalle(NkRender3D *r3d, NkMeshSystem *meshes) {
        const NkVec3f grisMur = { 0.72f, 0.70f, 0.66f };
        const NkVec3f grisSol = { 0.38f, 0.36f, 0.34f };
        const NkVec3f bois = { 0.55f, 0.38f, 0.22f };
        const NkVec3f vitre = { 0.75f, 0.85f, 0.92f };

        { // le sol
            NkDrawCall3D dc;
            dc.mesh = meshes->GetPlane();
            dc.transform = NkMat4f::Scale({ kPiece, 1.f, kPiece });
            dc.aabb = { { -kDemi, 0.f, -kDemi }, { kDemi, 0.f, kDemi } };
            dc.castShadow = false;
            dc.tint = grisSol;
            dc.metallic = 0.f;
            dc.roughness = 1.f;
            r3d->Submit(dc);
        }

        const float32 yMur = kPlafond * 0.5f;
        const float32 bord = kDemi + kMur * 0.5f;

        Pave(r3d, meshes, { 0.f, yMur, -bord }, { kPiece, kPlafond, kMur }, grisMur);
        Pave(r3d, meshes, { 0.f, yMur, bord }, { kPiece, kPlafond, kMur }, grisMur);
        Pave(r3d, meshes, { -bord, yMur, 0.f }, { kMur, kPlafond, kPiece }, grisMur);
        Pave(r3d, meshes, { bord, yMur, 0.f }, { kMur, kPlafond, kPiece }, grisMur);

        Pave(r3d, meshes, { 0.f, kPlafond + kMur * 0.5f, 0.f },
             { kPiece, kMur, kPiece }, grisMur);

        Pave(r3d, meshes, { -0.70f, kPorteH * 0.5f, -kDemi + 0.02f },
             { kPorteL, kPorteH, 0.04f }, bois, 0.6f);

        Pave(r3d, meshes, { -kDemi + 0.02f, kFenY, -0.90f },
             { 0.04f, kFenH, kFenL }, vitre, 0.15f);
        Pave(r3d, meshes, { -kDemi + 0.02f, kFenY, 0.90f },
             { 0.04f, kFenH, kFenL }, vitre, 0.15f);

        const float32 tx = 0.60f, tz = 0.70f;
        const float32 ep = 0.05f;
        Pave(r3d, meshes, { tx, kTableH - ep * 0.5f, tz },
             { kTableL, ep, kTableP }, bois, 0.5f);

        const float32 pied = 0.06f;
        const float32 hp = kTableH - ep;
        for (int i = 0; i < 4; ++i) {
            const float32 dx = ((i & 1) ? 1.f : -1.f) * (kTableL * 0.5f - pied);
            const float32 dz = ((i & 2) ? 1.f : -1.f) * (kTableP * 0.5f - pied);
            Pave(r3d, meshes, { tx + dx, hp * 0.5f, tz + dz },
                 { pied, hp, pied }, bois, 0.6f);
        }

        Pave(r3d, meshes, { -1.10f, 0.50f, 1.20f }, { 1.f, 1.f, 1.f },
             { 0.85f, 0.80f, 0.30f }, 0.8f);
    }


    // ── Sorties : chaque ligne va à l'écran ET dans le fichier de résultats ──
    std::FILE *gFichier = nullptr;
    void Ecrire(const char *fmt, ...) {
        va_list a;
        va_start(a, fmt);
        std::vprintf(fmt, a);
        va_end(a);
        if (gFichier) {
            va_start(a, fmt);
            std::vfprintf(gFichier, fmt, a);
            va_end(a);
        }
    }
    void OuvrirSortie(const char *nom, const char *mode) { gFichier = std::fopen(nom, mode); }
    void FermerSortie() {
        if (gFichier) {
            std::fclose(gFichier);
            gFichier = nullptr;
        }
    }

    // Sensibilité de la souris, en radians par « compte » du capteur. Négative :
    // souris vers la droite = tête vers la droite (un lacet positif tourne à gauche).
    const float32 kSensibilite = -0.0025f;
    const float32 kPi = 3.14159265358979f;
    const float32 kRadEnDeg = 180.f / kPi;
    const float32 kTangageMax = 89.f * kPi / 180.f; // bornes du tangage : +-89 degrés, pas 90
    // Exercice 10 : la matrice de projection décentrée, écrite à la main.
    // Angles en radians, signés : gauche et bas sont négatifs.
    // NkMat4f range ses coefficients par colonne : mat[colonne][ligne].
    NkMat4f Projection(float32 gauche, float32 droite, float32 haut, float32 bas,
                       float32 nearPlane, float32 farPlane) {
        const float32 tanLeft = std::tan(gauche);
        const float32 tanRight = std::tan(droite);
        const float32 tanUp = std::tan(haut);
        const float32 tanDown = std::tan(bas);
        const float32 tanWidth = tanRight - tanLeft;
        const float32 tanHeight = tanUp - tanDown;

        NkMat4f result;                       // la matrice NULLE (pas l'identité)
        result.mat[0][0] = 2.f / tanWidth;
        result.mat[1][1] = 2.f / tanHeight;
        result.mat[2][0] = (tanRight + tanLeft) / tanWidth;    // décentrage horizontal
        result.mat[2][1] = (tanUp + tanDown) / tanHeight;      // décentrage vertical
        result.mat[2][3] = -1.f;
        result.mat[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
        result.mat[3][2] = 2.f * farPlane * nearPlane / (nearPlane - farPlane);
        return result;
    }

    // Imprime les écarts coefficient par coefficient, une ligne de matrice par ligne.
    float32 ImprimerEcarts(const char *nom, const NkMat4f &a, const NkMat4f &b) {
        float32 maxi = 0.f;
        for (int ligne = 0; ligne < 4; ++ligne) {
            float32 e[4];
            for (int col = 0; col < 4; ++col) {
                e[col] = std::fabs(a.mat[col][ligne] - b.mat[col][ligne]);
                if (e[col] > maxi) maxi = e[col];
            }
            Ecrire("%s, ligne %d : %.8f %.8f %.8f %.8f\n", nom, ligne, e[0], e[1], e[2], e[3]);
        }
        return maxi;
    }

    void ComparerProjections() {
        const float32 nearPlane = 0.05f, farPlane = 100.f;
        const float32 deg = 3.14159265358979f / 180.f;

        // Épreuve symétrique : 70 degrés verticalement, rapport 1280/720.
        const float32 aspect = 1280.f / 720.f;
        const float32 haut = 35.f * deg;                          // 70 / 2
        const float32 droite = std::atan(std::tan(haut) * aspect); // tan(droite) = tan(haut) * aspect
        const NkMat4f maMat = Projection(-droite, droite, haut, -haut, nearPlane, farPlane);
        const NkMat4f ref = NkMat4f::Perspective(NkAngle(70.f), aspect, nearPlane, farPlane);
        const float32 e1 = ImprimerEcarts("symetrique", maMat, ref);

        // Épreuve quest : l'oeil gauche d'un Quest 2 (gauche -52, droite 45, haut 48, bas -50).
        const float32 g = -52.f * deg, d = 45.f * deg, h = 48.f * deg, b = -50.f * deg;
        const NkMat4f maQuest = Projection(g, d, h, b, nearPlane, farPlane);
        NkCamera3D cam;
        cam.SetNearFar(nearPlane, farPlane);
        cam.SetFovAsym(g, d, h, b);
        const float32 e2 = ImprimerEcarts("quest", maQuest, cam.GetProj());

        Ecrire("symetrique : plus grand ecart %.8f\n", (double)e1);
        Ecrire("quest : plus grand ecart %.8f\n", (double)e2);

        // Les coefficients du décentrage, pour la réponse :
        std::printf("quest, mat[2][0] = %.6f, mat[2][1] = %.6f\n", maQuest.mat[2][0], maQuest.mat[2][1]);
        std::printf("symetrique, mat[2][0] = %.6f, mat[2][1] = %.6f\n", maMat.mat[2][0], maMat.mat[2][1]);
    }

} // namespace

int nkmain(const NkEntryState &state) {
    OuvrirSortie("ecarts.txt", "w");
    ComparerProjections();
    FermerSortie();


    NkWindowConfig cfg;
    cfg.title = "Renderer And RHI";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("La fenetre n'a pas ete creee");
        return -1;
    }

    NkDeviceInitInfo devInit{};
    devInit.surface = window.GetSurfaceDesc();
    devInit.width = window.GetSize().x;
    devInit.height = window.GetSize().y;

    NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInit);
    if (device == nullptr) {
        logger.Error("Echec de creation du device");
        return -2;
    }

    logger.Info("[Render] API graphique retenue : {0}, surface de {1}x{2}", NkGraphicsApiName(devInit.api), devInit.width, devInit.height);

    NkRendererConfig cfgEcran = NkRendererConfig::For2D(devInit.api, devInit.width, devInit.height);
    NkRenderer *rEcran = NkRenderer::Create(device, cfgEcran);

    if (rEcran == nullptr || !rEcran->Initialize()) {
        logger.Error("Echec de creation du renderer");
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    NkOffscreenDesc od;
    od.width = devInit.width;
    od.height = devInit.height;
    od.hasDepth = true;
    od.hdr = false;
    od.colorFmt = NkGPUFormat::NK_RGBA8_UNORM;
    od.readable = true;
    od.readback = true; // sans quoi Capture() ne peut rien relire
    od.name = "Render_Cible";

    NkOffscreenTarget *cible = rEcran->CreateOffscreen(od);
    if (cible == nullptr) {
        logger.Error("[Render] cible hors ecran refusee");
        NkRenderer::Destroy(rEcran);
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    NkRendererConfig cfgScene = NkRendererConfig::ForGame(devInit.api, devInit.width, devInit.height);
    cfgScene.Disable(NK_SS_RENDER2D);
    cfgScene.Disable(NK_SS_TEXT);
    cfgScene.Disable(NK_SS_OVERLAY);
    cfgScene.Enable(NK_SS_OFFSCREEN);

    NkRenderer *renderer = NkRenderer::Create(device, cfgScene);
    if (renderer == nullptr || !renderer->Initialize()) {
        logger.Error("[Render] le renderer de la scene n'a pas pu s'initialiser");
        NkRenderer::Destroy(rEcran);
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    renderer->SetFinalColorTarget(rEcran->GetTextures()->GetRHIHandle(cible->GetColorResult()));

    auto &eventSystem = NkEvents();
    bool running = true;
    NkClock horloge;

    // ── Caméra : par défaut, celle de la salle ────────────────────────────
    NkVec3f camPos = { 0.30f, kYeux, 1.20f };
    NkVec3f camCible = { -0.7f, 1.10f, -kDemi };
    NkVec3f camHaut = { 0.f, 1.f, 0.f };
    EnvVec3("MASALLE_CAM", camPos);
    EnvVec3("MASALLE_TARGET", camCible);

    // ── Captures : « MASALLE_SHOT=120 » prend l'image 120 ──────────────────
    const int imageCapture = EnvInt("MASALLE_SHOT", -1);
    const char *cheminCapture = EnvStr("MASALLE_SHOT_PATH", "capture.png");
    int numeroImage = 0;


    while (running) {
        NkEvent *event;
        while (eventSystem.PollEvent(event)) {
            if (event->Is<NkWindowCloseEvent>()) {
                running = false;
            }

        }

        if (!running) break;

        const NkClock::NkTime &temps = horloge.Tick();

        if (rEcran->BeginFrame()) {
            NkICommandBuffer *cmd = rEcran->GetCmd();
            NkRender3D *r3d = renderer->GetRender3D();

            renderer->FlushGraphRebuilds();
            r3d->ResetFrame();
            if (auto *mc = renderer->GetMaterialCollection()) {
                mc->Upload();
            }


            NkCamera3DData cd;
            cd.position = camPos;
            cd.target = camCible;
            cd.up = camHaut;
            cd.fovY = 70.f;
            cd.aspect = (float32)devInit.width / (float32)devInit.height;
            cd.nearPlane = 0.05f;
            cd.farPlane = 100.f;

            NkSceneContext sctx;
            sctx.camera = NkCamera3D(cd);
            sctx.time = temps.total;

            NkLightDesc soleil;
            soleil.type = NkLightType::NK_DIRECTIONAL;
            soleil.direction = { -0.5f, -1.f, -0.35f };
            soleil.color = { 1.f, 0.96f, 0.88f };
            soleil.intensity = 3.f;
            soleil.castShadow = false;

            sctx.lights.PushBack(soleil);

            r3d->SetIBLStrength(0.35f);
            r3d->BeginScene(sctx);

            SoumettreLaSalle(r3d, renderer->GetMeshSystem());

            if (auto *graph = renderer->GetRenderGraph()) {
                graph->Execute(cmd);
            }

            if (auto *r2d = rEcran->GetRender2D()) {
                r2d->Begin(cmd, devInit.width, devInit.height);
                r2d->DrawImage(cible->GetColorResult(), { 0.f, 0.f, (float32)devInit.width, (float32)devInit.height });
                r2d->End();
            }

            rEcran->Present();
            rEcran->EndFrame();

            // Capture : la cible contient l'image APRÈS l'exécution du graphe.
            ++numeroImage;
            if (imageCapture >= 0 && numeroImage == imageCapture) {
                const bool ok = cible->Capture(cheminCapture);
                logger.Info("[Capture] image {0} -> {1} : {2}", numeroImage, cheminCapture, ok ? "ok" : "ECHEC");
                running = false;
            }
        } else {
            logger.Error("BeginFrame a refuse l'image");
        }
    }


    NkRenderer::Destroy(renderer);
    NkRenderer::Destroy(rEcran);
    NkDeviceFactory::Destroy(device);
    return 0;
}
