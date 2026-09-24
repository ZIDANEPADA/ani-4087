## Exercice 13 :
Lancez jenga info -v et rendez le tableau Available Toolchains en entier.

Dites ce qui est présent sur votre machine et ce qui manque. Si tout manque, c'est une réponse valable et elle vous dit quoi installer.

**Solution**
apres execution de la commande jenga info -v, j'obtient le tableau des Toolchains suivant:
```md
```bash
Available Toolchains
------------------------------------------------------------
Name               Family        Target OS   Arch     Env  
===========================================================
host-apple-clang   apple-clang   macOS       x86_64   gnu
clang-mingw        clang         Windows     x86_64   mingw
```

je constate que je n'ai aucune ligne qui correspond à Android. Donc aucun element de la suite Androide ne fonctionnera