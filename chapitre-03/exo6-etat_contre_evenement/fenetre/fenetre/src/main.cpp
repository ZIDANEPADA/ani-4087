#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState& state) {
    NkWindowConfig config;
    config.title = "Ma salle";
    config.width = 1280;
    config.height = 720;
   

    NkWindow fenetre(config);
    if (!fenetre.IsValid()){
        return 1;
    }
    auto& evenements = NkEvents();

    int compteurIsKeyDown = 0;
    int compteurKeyPressEvent = 0;

    //ecoute de NkKeyPressEven
    auto keyPress = evenements.AddEventCallbackGuard<NkKeyPressEvent>(
        [&](NkKeyPressEvent* event){
           if (event->GetKey() == NkKey::NK_SPACE){
                compteurKeyPressEvent++;
           }
        }
    );
    // ecout de la relache
    auto keyRelease = evenements.AddEventCallbackGuard<NkKeyReleaseEvent>(
        [&](NkKeyReleaseEvent* event){
            if (event->GetKey() == NkKey::NK_SPACE){
                std::cout << "\n  Resultas  \n";
                std::cout << "Compteur IsKeyDown : "
                          << compteurIsKeyDown << '\n';
                std::cout << "compteur KeyPressEvent : "
                          << compteurKeyPressEvent << '\n';
                std::cout << "Difference : "
                          << compteurIsKeyDown - compteurKeyPressEvent << '\n';
                std::cout << "\n";
            }
        }
    );

    while (fenetre.IsOpen()) {
        evenements.PollEvents();
        if (NkInput.IsKeyDown(NkKey::NK_SPACE)) {
            compteurIsKeyDown++;
        }
    }
    
    return 0;
}