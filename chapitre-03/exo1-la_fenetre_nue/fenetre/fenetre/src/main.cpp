#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title = "Ma salle";
    config.width = 1280;
    config.height = 720;
    //config.resizable = false;
    //config.movable = false;
    //config.hasShadow = false;
    //config.bgColor = 0xFFA500FF;
    //config.opacity = 0.5f;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()){
        return 1;
    }
    bool continuer = true;

    auto& evenements = NkEvents();

    auto fermeture = evenements.AddEventCallbackGuard<NkWindowCloseEvent>(
        [&](const NkWindowCloseEvent&) {
        continuer = false;
    });

    auto echap = evenements.AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* event) {
        if (event -> GetKey() == NkKey::NK_ESCAPE){
            fenetre.Close();
        }
    });

    while (continuer && fenetre.IsOpen()) {
        evenements.PollEvents();
    }
    
    return 0;
}