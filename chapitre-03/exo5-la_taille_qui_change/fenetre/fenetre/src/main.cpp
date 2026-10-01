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

    auto redimentionnement = evenements.AddEventCallbackGuard<NkWindowResizeEvent>(
        [](NkWindowResizeEvent* event){
           std::cout << "Nouvelle taille : "
                     << event->GetWidth() << "x" 
                     << event->GetHeight() 
                     << '\n';
        }
    );

    while (fenetre.IsOpen()) {
        evenements.PollEvents();
    }
    
    return 0;
}