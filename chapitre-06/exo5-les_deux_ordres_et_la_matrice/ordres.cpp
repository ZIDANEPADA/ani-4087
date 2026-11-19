// Exercice 5 - Les deux ordres, et la matrice
// Le calcul tourne au demarrage, avant la fenetre ; les 3 lignes vont a l'ecran et dans regards.txt.

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
    // Exercice 5 : trois façons de construire l'orientation d'une tête.
    // lacet = 45 degrés (autour de l'axe vertical Y), tangage = 30 degrés (autour de X).
    void CalculerOrdres() {
        const float32 lacetDeg = 45.f;
        const float32 tangageDeg = 30.f;
        const NkVec3f avant(0.f, 0.f, -1.f); // l'avant de la salle

        const NkQuatf qLacet = NkQuatf::RotateY(NkAngle(lacetDeg));
        const NkQuatf qTangage = NkQuatf::RotateX(NkAngle(tangageDeg));

        // 1) et 2) : les deux produits de quaternions, appliqués à l'avant
        const NkVec3f a = (qLacet * qTangage) * avant;
        const NkVec3f b = (qTangage * qLacet) * avant;

        // 3) le chemin du simulateur : deux matrices, puis conversion en quaternion
        const NkMat4f rotation = NkMat4f::RotationY(NkAngle(lacetDeg)) *
                                 NkMat4f::RotationX(NkAngle(tangageDeg));
        const NkQuatf q = NkQuatf(rotation).Normalized();
        const NkVec3f c = q * avant;

        Ecrire("lacet*tangage : (%.4f, %.4f, %.4f)\n", a.x, a.y, a.z);
        Ecrire("tangage*lacet : (%.4f, %.4f, %.4f)\n", b.x, b.y, b.z);
        Ecrire("matrices : (%.4f, %.4f, %.4f)\n", c.x, c.y, c.z);

        // Vérification À LA MAIN : une tête qui a levé les yeux de 30 degrés regarde
        // vers le haut avec y = sin(30 deg) = 0,5 ; quel que soit le lacet.
        const float32 yMain = std::sin(30.f * 3.14159265358979f / 180.f);
        std::printf("a la main : y = sin(30 deg) = %.4f\n", yMain);
        std::printf("ecart de y avec la main : lacet*tangage %.4f, tangage*lacet %.4f, matrices %.4f\n",
                    std::fabs(a.y - yMain), std::fabs(b.y - yMain), std::fabs(c.y - yMain));
    }

} // namespace

int nkmain(const NkEntryState &state) {
    OuvrirSortie("regards.txt", "w");
    CalculerOrdres();
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
