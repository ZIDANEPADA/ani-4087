## Exercice 6 : Etat contre événement

Écrivez deux compteurs. Le premier s'incrémente à chaque image où la touche Espace est tenue, lu par NkInput.IsKeyDown. Le second s'incrémente à chaque NkKeyPressEvent sur Espace.

Appuyez une seconde, relâchez. Rendez les deux nombres et expliquez l'écart.

# Reponse
```md
```bash
  Resultas  
Compteur IsKeyDown : 80509
compteur KeyPressEvent : 1
Difference : 80508

```

La touche est maintenue pendant une seconde. La boucle effectue plusieurs dizaines de passages pendant cette période, le compteur d'état augmente plusieurs dizaines de fois. Le compteur d'événements augmente lors de la pression initiale, sans compter chaque image pendant laquelle le doigt reste sur la touche.
Le nombre exact dépend du nombre d'images traitées et des règles de répétition des événements.

Conclusion : l'état sert à représenter une condition persistante, tandis que l'événement sert à représenter une action ponctuelle. Un déplacement continu est vu comme une lecture d'état ; une action unique comme le tir se prête à l'événement.

## code de test
```md
```cpp
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
    // ecoute de la relace
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
```