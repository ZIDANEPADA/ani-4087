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
    // curseur cache et confine
    fenetre.ShowMouse(true);
    fenetre.ClipMouseToClient(false);


    while (fenetre.IsOpen()) {

    while (NkEvent *ev = evenements.PollEvent()) {

        if (auto *mouse = ev->As<NkMouseMoveEvent>()) {

            std::cout
                << "x=" << mouse->GetX()
                << " y=" << mouse->GetY()
                << " deltaX=" << mouse->GetDeltaX()
                << " deltaY=" << mouse->GetDeltaY()
                << std::endl;
        }
    }
}
    // fenetre.ClipMouseToClient(false);
    // fenetre.ShowMouse(true);
    
    return 0;
}