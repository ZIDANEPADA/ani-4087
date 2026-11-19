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
#include "NKRenderer/Core/NkTextureLibrary.h"
#include "NKRenderer/Materials/NkMaterialCollection.h"
#include "NKRenderer/Mesh/NkMeshSystem.h"
#include "NKRenderer/Tools/Offscreen/NkOffscreenTarget.h"
#include "NKRenderer/Tools/Render2D/NkRender2D.h"
#include "NKRenderer/Tools/Render3D/NkRender3D.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

namespace {

    // ── Les dimensions de la salle, en un seul endroit ────────────────────
    // Elles sont ici, nommées, et pas semées dans le code : au chapitre 21 on
    // les lira depuis un fichier, et ce sont ces noms-là qui deviendront des
    // champs.
    const float32 kPiece = 4.00f;      // côté intérieur du sol
    const float32 kPlafond = 2.50f;      // hauteur sous plafond
    const float32 kMur = 0.10f;          // épaisseur d'un mur
    const float32 kPorteL = 0.90f;      // porte : largeur
    const float32 kPorteH = 2.00f;      //         hauteur
    const float32 kFenL = 1.20f;      // fenêtre : largeur
    const float32 kFenH = 1.00f;      //           hauteur
    const float32 kFenY = 1.40f;      //           hauteur de son centre
    const float32 kTableL = 1.20f;      // table : longueur
    const float32 kTableP = 0.80f;      //         profondeur
    const float32 kTableH = 0.75f;      //         hauteur du plateau
    const float32 kYeux = 1.70f;      // hauteur des yeux, debout

    const float32 kDemi = kPiece * 0.5f;

    // Un pavé posé dans la salle. `centre` est le centre géométrique, `taille`
    // les trois dimensions en mètres : on ne manipule jamais autre chose.
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

        { // le sol : le plan est unitaire, une échelle S donne un côté S
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

        // Quatre murs. La porte est dans celui du fond, les fenêtres à gauche.
        Pave(r3d, meshes, { 0.f, yMur, -bord }, { kPiece, kPlafond, kMur }, grisMur);
        Pave(r3d, meshes, { 0.f, yMur, bord }, { kPiece, kPlafond, kMur }, grisMur);
        Pave(r3d, meshes, { -bord, yMur, 0.f }, { kMur, kPlafond, kPiece }, grisMur);
        Pave(r3d, meshes, { bord, yMur, 0.f }, { kMur, kPlafond, kPiece }, grisMur);

        // Le plafond. On l'oublie toujours, et le trou ne se voit qu'en levant
        // les yeux, c'est-à-dire le jour de la démonstration.
        Pave(r3d, meshes, { 0.f, kPlafond + kMur * 0.5f, 0.f },
             { kPiece, kMur, kPiece }, grisMur);

        // La porte, fermée jusqu'au chapitre 17 : un panneau plaqué contre le
        // mur du fond, décalé pour ne pas se battre avec lui en profondeur.
        Pave(r3d, meshes, { -0.70f, kPorteH * 0.5f, -kDemi + 0.02f },
             { kPorteL, kPorteH, 0.04f }, bois, 0.6f);

        // Deux fenêtres sur le mur de gauche, pour qu'il y ait un dehors.
        Pave(r3d, meshes, { -kDemi + 0.02f, kFenY, -0.90f },
             { 0.04f, kFenH, kFenL }, vitre, 0.15f);
        Pave(r3d, meshes, { -kDemi + 0.02f, kFenY, 0.90f },
             { 0.04f, kFenH, kFenL }, vitre, 0.15f);

        // La table : un plateau et quatre pieds. Le chapitre 12 y posera un
        // objet, le 21 la déplacera.
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

        // Le repère d'un mètre du chapitre 9 : un cube d'un mètre de côté,
        // posé au sol, contre lequel on juge l'échelle de tout le reste.
        Pave(r3d, meshes, { -1.10f, 0.50f, 1.20f }, { 1.f, 1.f, 1.f },
             { 0.85f, 0.80f, 0.30f }, 0.8f);
    }

} // namespace

int nkmain(const NkEntryState &state) {

    NkWindowConfig cfg;
    cfg.title = "Renderer And RHI";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("La fenetre n'a pas ete creee");
        return -1;
    }

    // ── Le périphérique ────────────────────────────────────────────────────
    // 1. Ce qu'on veut : dessiner DANS cette fenêtre, à cette taille.
    NkDeviceInitInfo devInit{};
    devInit.surface = window.GetSurfaceDesc();
    devInit.width = window.GetSize().x;
    devInit.height = window.GetSize().y;
    // devInit.api = NkGraphicsApi::NK_GFX_API_OPENGL;

    // 2. Le moteur essaie les API de la machine et garde la première qui
    //    répond. Il ÉCRIT son choix dans devInit.api : c'est pour cela que la
    //    fonction prend devInit par référence, et non par copie.
    NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInit);
    if (device == nullptr) {
        logger.Error("Echec de creation du device");
        return -2;
    }

    logger.Info("[Render] API graphique retenue : {0}, surface de {1}x{2}", NkGraphicsApiName(devInit.api), devInit.width, devInit.height);

    // ── Le renderer de l'écran : il possède l'image et la présente ─────────
    NkRendererConfig cfgEcran = NkRendererConfig::For2D(devInit.api, devInit.width, devInit.height);
    NkRenderer *rEcran = NkRenderer::Create(device, cfgEcran);

    if (rEcran == nullptr || !rEcran->Initialize()) {
        logger.Error("Echec de creation du renderer");
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    // ── La cible hors écran : la texture dans laquelle la scène est dessinée ─
    NkOffscreenDesc od;
    od.width = devInit.width;
    od.height = devInit.height;
    od.hasDepth = true; // sans profondeur, le fond se dessine par-dessus le devant
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

    // ── Le renderer de la scène : il dessine en 3D dans la cible ───────────
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

    const float32 kPiece = 4.00f; // côté du sol, en mètres
    const float32 kYeux = 1.70f;  // hauteur des yeux, debout
    const float32 kDemi = kPiece * 0.5f;

    auto &eventSystem = NkEvents();
    bool running = true;

    // L'horloge du moteur. Un Tick() par image rend la durée de l'image
    // (delta) et le temps écoulé depuis le démarrage (total), en secondes.
    NkClock horloge;

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

            // Ce que BeginFrame ferait si ce renderer possédait l'image. En
            // mode partagé, on le rejoue à la main. Oublier ResetFrame piétine
            // les tampons d'une image à l'autre.
            renderer->FlushGraphRebuilds();
            r3d->ResetFrame();
            if (auto *mc = renderer->GetMaterialCollection()) {
                mc->Upload();
            }

            // ── La caméra : où l'on est, ce qu'on regarde, où est le haut ──
            NkCamera3DData cd;
            cd.position = { 0.30f, kYeux, 1.20f };
            cd.target = { -0.7f, 1.10f, -kDemi };
            cd.up = { 0.f, 1.f, 0.f };
            cd.fovY = 70.f;
            cd.aspect = (float32)devInit.width / (float32)devInit.height;
            cd.nearPlane = 0.05f;
            cd.farPlane = 100.f;

            // ── Le contexte de la scène : la caméra, le temps, les lumières ──
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

            r3d->SetIBLStrength(0.35f); // la part de lumière qui vient du ciel
            r3d->BeginScene(sctx);

            SoumettreLaSalle(r3d, renderer->GetMeshSystem());
            // { // le sol : le plan est unitaire, une échelle S donne un côté S
                // NkDrawCall3D dc;
                // dc.mesh = renderer->GetMeshSystem()->GetPlane();
                // dc.transform = NkMat4f::Scale({ kPiece, 1.f, kPiece });
                // dc.aabb = { { -kDemi, 0.f, -kDemi }, { kDemi, 0.f, kDemi } };
                // dc.castShadow = false;
                // dc.tint = { 0.38f, 0.36f, 0.34f };
                // dc.metallic = 0.f;
                // dc.roughness = 1.f;
                // r3d->Submit(dc);
            // }
            
            // {
                // const NkVec3f centre = { 0.f, 0.50f, 0.f };
                // const NkVec3f taille = { 1.f, 1.f, 1.f };
                // const NkVec3f teinte = { 0.85f, 0.80f, 0.30f };
                // float32 rugosite = 0.8f;
                
                // NkDrawCall3D dc;
                // dc.mesh = renderer->GetMeshSystem()->GetCube();
                // // On lit de droite à gauche : d'abord l'échelle, puis la translation.
                // dc.transform = NkMat4f::Translate(centre) * NkMat4f::Scale(taille);
                // // La boîte englobante, dans le monde : le moteur s'en sert pour écarter
                // // ce qui est hors du champ. Fausse, l'objet disparaît sans un mot.
                // dc.aabb = { { centre.x - taille.x * 0.5f, centre.y - taille.y * 0.5f,
                              // centre.z - taille.z * 0.5f },
                            // { centre.x + taille.x * 0.5f, centre.y + taille.y * 0.5f,
                              // centre.z + taille.z * 0.5f } };
                // dc.tint = teinte;
                // dc.metallic = 0.f;
                // dc.roughness = rugosite;
                // r3d->Submit(dc);
            // }

            // Le graphe de la scène s'exécute sur le tampon de commandes de
            // l'écran, AVANT son Present. Après lui, la cible contient l'image.
            if (auto *graph = renderer->GetRenderGraph()) {
                graph->Execute(cmd);
            }

            // La texture, montrée dans la fenêtre. Un dessin 2D ne part vers
            // la carte que s'il est émis ENTRE Begin et End : Begin donne au
            // rendu 2D le tampon de commandes de l'image, End envoie la liste.
            if (auto *r2d = rEcran->GetRender2D()) {
                r2d->Begin(cmd, devInit.width, devInit.height);
                r2d->DrawImage(cible->GetColorResult(), { 0.f, 0.f, (float32)devInit.width, (float32)devInit.height });
                r2d->End();
            }

            rEcran->Present();
            rEcran->EndFrame();
        } else {
            logger.Error("BeginFrame a refuse l'image");
        }
    }

    NkRenderer::Destroy(renderer);
    NkRenderer::Destroy(rEcran);
    NkDeviceFactory::Destroy(device);
    return 0;
}
