## Exercice 3 : Cinq champs de configuration

Modifiez cinq champs de NkWindowConfig que le chapitre n'a pas montrés, choisis dans NkWindowConfig.h.

Pour chacun, rendez la ligne, ce que vous attendiez, et ce que vous avez observé. Un champ qui n'a rien changé est une réponse valable, à condition de dire pourquoi vous le pensez.
# Reponse
Voici les différents champs que je vais tester :
---------------------------------------------------------------------------------------------------------------------------------------------
|Champs         |   Ligne de la configuration |                   Résultat attendu |                   Observation réelle                    |
|---------------|-----------------------------|------------------------------------|---------------------------------------------------------|
| resizable     | config.resizable = false;   |Interdire le redimentionnement      | Redimentionnement interdit                              |
| movable       | config.movable = false;     |Interdire le deplacement            | La fenetre se deplace toujours                          |
| hasShadow     | config.hasShadow = false;   |Désactive l'ombre de la fenêtre     | L'ombre a été desactive                                 |
| bdColor       | config.bgColor = 0xFFA500FF;|Changer la couleur d'arrire plan    | La couleur n'a pas changé                               |
| opacity       | config.opacity = 0.5f;      |Rendre la fenetre transparente      | La fenetre est devenue tranparente                      |
|---------------|-----------------------------|------------------------------------|---------------------------------------------------------|

# Champ : resizable (bool)

**Modification effectuée** : La valeur initiale de ce champ est *true* a été remplacée par *fals* pour le test.

**Résultat attendu** : En appliquant ce champ la dimention de la fenetre ne doit plus etre modifiable.

**Résultat observé** : Apres avoir aplliqué ce champ, la fenetre ne pouvait plus etre réduite ou agrandie.

**Interprétation** : Le résultat confirme effectivement mon attente.

# Champ : movable (bool)

**Modification effectuée** : La valeur initiale de ce champ est *true* a été remplacée par *fals* pour le test.

**Résultat attendu** : En appliquant ce champ la fenetre doit rester à une seule position sans pour être deplacée.

**Résultat observé** : Apres avoir aplliqué ce champ, la fenetre parviens toujours à être déplacée.

**Interprétation** : Le résultat confirme pas mon attente, il s'agit peut-être d'une différence de plateforme, de configuration ou d'implémentation.

# Champ : hasShadow (bool)

**Modification effectuée** : La valeur initiale de ce champ est *true* a été remplacée par *fals* pour le test.

**Résultat attendu** : En appliquant ce champ la fenetre ne doit plus avoir d'ombre.

**Résultat observé** : Apres avoir aplliqué ce champ, l'ombre de la fenetre ne se montre plus'.

**Interprétation** : Le résultat confirme effectivement mon attente.

# Champ : bgColor (uint32)

**Modification effectuée** : La valeur initiale de ce champ est *0x141414FF* a été remplacée par *0xFFA500FF* pour le test.

**Résultat attendu** : En appliquant ce champ la couler de fenetre doit etre Orange.

**Résultat observé** : Apres avoir aplliqué ce champ, la fenetre garde toujours sa couleur de base.

**Interprétation** : Le résultat ne confirme pas attente, il s'agit peut-etre d'une différence de plateforme, de configuration ou d'implémentation.

# Champ : opacity (float32)

**Modification effectuée** : La valeur initiale de ce champ est *1.0* a été remplacée par *0.5* pour le test.

**Résultat attendu** : En appliquant ce champ la fenetre doit etre transparente.

**Résultat observé** : Apres avoir aplliqué ce champ, la fenetre transparente, je peux voir les ellement de fenetre en arriere.

**Interprétation** : Le résultat confirme effectivement mon attente.

