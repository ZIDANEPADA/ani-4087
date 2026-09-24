## Demonstration 1 :
Montrez à la classe une erreur volontaire dans le fichier de projet, d'abord vue par jenga build, puis par jenga info.

Faites dire à la classe laquelle des deux sorties désigne la cause.

Pour ce cas ci je vais simplement vider le fichier *main.cpp*
lorsque je lance jenga build j'obtient la sortie:
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

Configuration: Debug
Target:        macOS x86_64
Toolchain:     host-apple-clang

Build Order (1 projects):
  1. demo [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: demo                                                            Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: Link Failed                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ Undefined symbols for architecture x86_64:                                                   ║
║   "_main", referenced from:                                                                  ║
║      implicit entry/start for main executable                                                ║
║ ld: symbol(s) not found for architecture x86_64                                              ║
║ clang: error: linker command failed with exit code 1 (use -v to see invocation)              ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝
✗ Link failed: Build/Bin/Debug-macOS/demo/demo

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 1.78s  │
│ Errors: 1  | Failed files: 1                                                                 │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  0/1
Failed:         1
Errors:         1
Time:           1.86s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ demo
  ```
  par contre la sortie de jenga info n'est pas differente de lorsque le fichier main etait encore intacte
  la sortie obtenue est:
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

============================ Jenga Workspace: demo =============================

Location: /Users/user/Desktop/Transition/AIA4/ani-4087/chapitre-02/demo1-info_contre_build/demo
Entry file: /Users/user/Desktop/Transition/AIA4/ani-4087/chapitre-02/demo1-info_contre_build/demo/demo.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Linux, macOS, Android, iOS, Web
Target Architectures: x86_64, x86, arm64, arm, wasm32


Projects
------------------------------------------------------------
Name   Kind         Language   Test   External
==============================================
demo   ConsoleApp   C++        No     Yes


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

On constate ici que build revele l'erreur d'execution de la configuration tandis que info mpntre ce que jenga a compris du projet