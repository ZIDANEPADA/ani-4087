#include <iostream>
#include <chrono>

#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"

#include "NKRHI/Core/NkDeviceFactory.h"
#include "NKRenderer/NkRenderer.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState& state) {
    (void)state;

    // ------------------------------------------------------------
    // 1. Création de la fenêtre
    // ------------------------------------------------------------
    NkWindowConfig winCfg;
    winCfg.title = "Mesure NK_SS_ALL";
    winCfg.width = 1280;
    winCfg.height = 720;
    winCfg.centered = true;
    winCfg.resizable = true;

    NkWindow window(winCfg);

    if (!window.IsValid()) {
        std::cerr << "Erreur : impossible de créer la fenêtre." << std::endl;
        return 1;
    }

    // ------------------------------------------------------------
    // 2. Création du device graphique
    // ------------------------------------------------------------
    NkDeviceInitInfo devInfo{};

    devInfo.surface = window.GetSurfaceDesc();
    devInfo.width = (uint32)window.GetSize().width;
    devInfo.height = (uint32)window.GetSize().height;

    NkIDevice* device = NkDeviceFactory::CreateAutoDetect(devInfo);

    if (!device || !device->IsValid()) {
        std::cerr << "Erreur : impossible de créer le device." << std::endl;
        window.Close();
        return 2;
    }

    // ------------------------------------------------------------
    // 3. Configuration du renderer
    // ------------------------------------------------------------
    NkRendererConfig cfg =
        NkRendererConfig::ForGame(
            devInfo.api,
            devInfo.width,
            devInfo.height
        );

    // Configuration demandée par l'exercice
    cfg.subsystems = NK_SS_ALL;

    // ------------------------------------------------------------
    // 4. Mesure de l'initialisation du renderer
    // ------------------------------------------------------------
    auto debut = std::chrono::steady_clock::now();

    NkRenderer* renderer = NkRenderer::Create(device, cfg);

    bool initialise = false;

    if (renderer) {
        initialise = renderer->Initialize();
    }

    auto fin = std::chrono::steady_clock::now();

    // ------------------------------------------------------------
    // 5. Vérification
    // ------------------------------------------------------------
    if (!renderer || !initialise) {
        std::cerr << "Erreur : impossible d'initialiser NKRenderer."
                  << std::endl;

        NkRenderer::Destroy(renderer);
        NkDeviceFactory::Destroy(device);
        window.Close();

        return 3;
    }

    // ------------------------------------------------------------
    // 6. Calcul du temps
    // ------------------------------------------------------------
    auto duree =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            fin - debut
        ).count();

    // Une seule ligne : pratique pour mesures.txt
    std::cout << duree << std::endl;

    // ------------------------------------------------------------
    // 7. Nettoyage
    // ------------------------------------------------------------
    NkRenderer::Destroy(renderer);
    NkDeviceFactory::Destroy(device);
    window.Close();

    return 0;
}