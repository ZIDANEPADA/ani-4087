## Exercice 4 : Fermer proprement 

Ajoutez un rappel sur NkWindowCloseEvent qui met un booléen à faux, et faites porter la boucle sur ce booléen plutôt que sur IsOpen().

Ajoutez ensuite un rappel sur NkKeyPressEvent qui fait la même chose sur la touche Échap.

Rendez le code et expliquez pourquoi les deux chemins de sortie doivent aboutir au même endroit.

# Reponse

voici le code avec lequel j'ai travaillé
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
```


# Pourquoi les deux chemins doivent-ils aboutir au même endroit ?

La fermeture par la croix et la fermeture par Échap sont deux événements différents, mais elles expriment la même intention de l'utilisateur : **quitter l'application**.
En modifiant le même booléen, on évite de dupliquer la logique de sortie. On peut ensuite ajouter au même endroit une sauvegarde, une libération de ressources ou une confirmation de fermeture si le projet en a besoin.
Les objets retournés par AddEventCallbackGuard contrôlent la durée de vie des rappels. Ils doivent rester vivants aussi longtemps que les rappels doivent fonctionner. Leur destruction permet leur désinscription, évitant de conserver des callbacks devenus inutiles.