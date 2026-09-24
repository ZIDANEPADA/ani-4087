## Exercice 2: Info avant build
Lancez *jenga info* sur votre projet et lisez sa sortie en entier. Rendez-la, et dites ce qu'elle vous apprend que le fichier de projet ne disait pas explicitement.
Lorsque je lance jenga build sur le projet de ma salle j'obtient la sortie suivante:

## Sortie de jenga build:
```bash
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.7.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

======================== Jenga Workspace: work_ani_4087 ========================

Location: /Users/user/Desktop/Transition/AIA4/ani-4087/chapitre-02/exo1-le_projet_minimal/work_ani_4087
Entry file: /Users/user/Desktop/Transition/AIA4/ani-4087/chapitre-02/exo1-le_projet_minimal/work_ani_4087/work_ani_4087.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: macOS
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name        Kind         Language   Test   External
===================================================
MaSalle_z   ConsoleApp   C++        No     Yes


Available Toolchains
------------------------------------------------------------
Name               Family        Target OS   Arch     Env  
===========================================================
host-apple-clang   apple-clang   macOS       x86_64   gnu
clang-mingw        clang         Windows     x86_64   mingw


Daemon
------------------------------------------------------------
```
Ce que jenga info me dit et que le fichier projet ne disait pas explicitement c'est que :
- j'ai refusé les tests unitaires (j'ai pourtant accepté lord de la création)
- les differents toolchains, leur famille, le systeme sur lequel il est utilise, son architecture et son Env