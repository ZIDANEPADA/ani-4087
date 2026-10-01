## Exercice 7 : Le pointeur caché

Cachez le curseur et confinez-le. Affichez à chaque image la position x, y et le rawDelta.

Bougez la souris jusqu'à ce qu'elle atteigne le bord. Rendez les deux séries et dites laquelle continue de bouger, et pourquoi c'est celle-là qu'il faut.

# Reponse
mon resultat
```md
```bash
x=19 y=694 deltaX=0 deltaY=0
x=18 y=695 deltaX=0 deltaY=-1
x=18 y=695 deltaX=0 deltaY=0
x=18 y=696 deltaX=0 deltaY=0
x=18 y=697 deltaX=-1 deltaY=-1
x=17 y=697 deltaX=0 deltaY=-1
x=17 y=697 deltaX=0 deltaY=0
x=17 y=698 deltaX=0 deltaY=-1
x=17 y=698 deltaX=-1 deltaY=0
x=17 y=698 deltaX=0 deltaY=0
x=17 y=699 deltaX=0 deltaY=-1
x=17 y=699 deltaX=0 deltaY=0
x=17 y=700 deltaX=0 deltaY=0
x=16 y=700 deltaX=0 deltaY=0
x=16 y=700 deltaX=0 deltaY=-1
x=16 y=700 deltaX=0 deltaY=0
x=16 y=700 deltaX=-1 deltaY=0
x=16 y=701 deltaX=0 deltaY=-1
```

Quand la souris se déplace vers le bord de la fenêtre, sa position `x` et `y` évolue progressivement dans la zone confinée. Dans les mesures obtenues, on observe par exemple des positions passant de `(19, 694)` à `(16, 700)`. La position représente donc les coordonnées absolues du pointeur dans la fenêtre.
Les valeurs `deltaX` et `deltaY`, quant à elles, représentent le déplacement relatif associé aux événements de mouvement. Elles sont nulles lorsque aucun déplacement n'est détecté pour l'événement considéré, elles peuvent aussi prendre des petites valeurs comme `-1` lorsqu'un déplacement relatif est détecté. Par exemple, on observe `deltaX=-1, deltaY=-1` ou `deltaX=0, deltaY=-1`.

Ainsi, les deux séries ne représentent pas la même information : `x` et `y` indiquent la position absolue de la souris dans la fenêtre, tandis que `deltaX` et `deltaY` indiquent son déplacement relatif. Pour une interaction de type caméra, le **déplacement relatif** est donc la donnée pertinente, car il permet de **contrôler une rotation** même lorsque la position du pointeur est limitée par les frontières de la fenêtre.


Je tient à préciser que j'ai eu beaucoup de dificulté pour arriver à ce resulta. au départ j'ai utilié
```md
```cpp
        evenements.PollEvents();

        int32 x = NkInput.MouseX();
        int32 y = NkInput.MouseY();
        int32 rawDx = NkInput.MouseRawDeltaX();
        int32 rawDy = NkInput.MouseRawDeltaY();
```
Qui ne tient apparement pas compte du deplacement relatif parce qu'il etait toujours à (0,0) apres plusieurs tantatives

Dans la suite j'ai utilisé le code suivant
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
```
