## Exercice 9:
Ajoutez à files un motif qui ne correspond à aucun fichier, et à includedirs un dossier qui n'existe pas.

Rendez ce que jenga info en dit, et ce que jenga build en dit. Comparez les deux : lequel vous aurait fait gagner du temps ?

## La sortie de jenga info
```md
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

[jenga] ATTENTION : defines() appele hors d'un projet et hors toolchain -> SANS EFFET : FILTRE_ACTIF
          Placez l'appel dans un `with project(...)`, une toolchain, ou un helper appele par chaque projet.
============================ Jenga Workspace: exo6 =============================

Location: /Users/user/Desktop/Transition/AIA4/ani-4087/chapitre-02/exo6-le_filtre_qui_ne_s_active_jamais/exo6
Entry file: /Users/user/Desktop/Transition/AIA4/ani-4087/chapitre-02/exo6-le_filtre_qui_ne_s_active_jamais/exo6/exo6.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: macOS
Target Architectures: x86_64, arm64


Projects
------------------------------------------------------------
Name   Kind         Language   Test   External
==============================================
exo6   ConsoleApp   C++        No     Yes


Available Toolchains
------------------------------------------------------------
Name               Family        Target OS   Arch     Env  
===========================================================
host-apple-clang   apple-clang   macOS       x86_64   gnu
clang-mingw        clang         Windows     x86_64   mingw


Daemon
------------------------------------------------------------
Status: Not running
```

## La sortie de jenga build
```md
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

Loading workspace...
[jenga] ATTENTION : defines() appele hors d'un projet et hors toolchain -> SANS EFFET : FILTRE_ACTIF
          Placez l'appel dans un `with project(...)`, une toolchain, ou un helper appele par chaque projet.

Configuration: Debug
Target:        macOS x86_64
Toolchain:     host-apple-clang

Build Order (1 projects):
  1. exo6 [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: exo6                                                            Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓ All files up to date
ℹ Linking...
✓ Built: Build/Bin/Debug-macOS/exo6/exo6

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.98s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.99s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════
  ```

  de ces deux sorties, jenga info décrit ce que jenga a compris du projet 
  jenga build est celui qui va reelement devoir utiliser les fichiers et les chemins pendant la construction. 
  **Selon moi celui qui m'aurait permit de gagner en temps est la sortie de *jenga build***