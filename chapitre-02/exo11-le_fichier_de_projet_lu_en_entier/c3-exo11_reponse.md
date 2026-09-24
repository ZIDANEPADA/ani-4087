## Exercice 11
Ouvrez le fichier de projet de la démonstration XR du moteur et lisez-le en entier, y compris les commentaires.

Rendez une page : ce qu'il construit, ce dont il dépend, ce qui change d'un système à l'autre, et les trois pièges qu'il documente. Pour chacun des trois, dites ce qui se passerait sans la ligne concernée.



1. Ce que construit mon projet

Le workspace s'appelle "work_ani_4087", il possède deux configurations de compilation : configurations **(['Debug', 'Release'])**

Le projet principal s'appelle "MaSalle_z".
```md
```python
with project("MaSalle_z"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])
```

le projet construit une application console en C++, le programme utilise le langage C++ avec le standard C++17.

Les fichiers sources sont recherchés dans le dossier "src" et les fichiers d'en-tête dans le dossier "include".

2. Ce dont le projet dépend

Le projet ne déclare jusqu'ici aucune bibliothèque externe avec "links()" et ne déclare pas non plus de dépendance entre plusieurs projets avec "dependson()". Il dépend principalement de ses propres fichiers :
```md
```python
files(["src/**.cpp", "include/**.hpp"])
```

Le fichier de workspace inclut également un autre fichier de configuration :
```md
```python
with include("MaSalle_z/MaSalle_z.jenga"):
    pass
```
Cela signifie que "MaSalle_z/MaSalle_z.jenga" fait partie de la configuration complète du projet et doit également être pris en compte lors de la lecture du projet.

3. Ce qui change d'un système à l'autre

Dans ce projet, aucune configuration différente n'est actuellement prévue pour Windows, Linux ou Android.

Le workspace contient explicitement :

targetoses([TargetOS.MACOS])
targetarchs([TargetArch.X86_64])

Le projet cible donc :

- système : macOS
- architecture : x86_64
- configurations : Debug et Release

Il ne contient actuellement aucun filtre du type :
```md
```python
with filter("system:Windows"):
```

ou :
```md
```python
with filter("system:Linux"):
```
ou encore une configuration Android.

Le projet n'est donc pas encore configuré pour être compilé pour plusieurs systèmes.

4. Les trois points importants à surveiller

**Piège 1 — "consoleapp()" au lieu de "windowedapp()"**

Le projet utilise : consoleapp(). Cela signifie qu'il produit une application console. Si on remplaçait cette ligne par :  windowedapp(). le type d'application changerait : Jenga construirait alors une application destinée à fonctionner avec une fenêtre plutôt qu'une application console.


**Piège 2 — La cible est limitée à macOS x86_64**

Le fichier contient :

targetoses([TargetOS.MACOS])
targetarchs([TargetArch.X86_64])

Ces lignes limitent la cible du workspace.

Le projet ne demande donc pas à Jenga de préparer une compilation pour Windows, Linux ou une autre architecture.

Sans cette configuration, ou avec une configuration différente, Jenga pourrait considérer d'autres cibles selon les toolchains et plateformes disponibles.

Ici, la configuration indique clairement que le projet est destiné à macOS x86_64.

**Piège 3 — Le deuxième fichier ".jenga" est inclus**

La dernière partie du workspace est :

```md
```python
with include("MaSalle_z/MaSalle_z.jenga"):
    pass
```

Il ne faut pas lire uniquement le fichier principal puis considérer que la configuration est complète.

Le fichier : MaSalle_z/MaSalle_z.jenga est également inclus dans le workspace.

Si cette ligne était supprimée, la configuration définie dans ce fichier ne serait plus prise en compte par le workspace principal.

1. Résumé

Mon workspace Jenga "work_ani_4087" contient un projet appelé "MaSalle_z". Il construit une application console C++17, avec deux configurations : Debug et Release. Les fichiers du programme sont pris dans les dossiers "src" et "include". Le workspace cible actuellement uniquement macOS x86_64. Contrairement à une configuration multi-plateforme, aucune section "filter()" pour Windows, Linux ou Android n'est présente dans le fichier fourni. Enfin, le workspace inclut un second fichier de projet : MaSalle_z/MaSalle_z.jenga.