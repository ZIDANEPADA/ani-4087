## Exerice 5 : 
Écrivez un petit en-tête à vous qui déclare une classe complète si un define est posé, et une coquille vide sinon. Compilez un programme qui l'emploie, avec puis sans le define.

Rendez les deux messages et dites lequel des deux vous auriez su diagnostiquer sans cet exercice.

voici les differents fichier avec lesquesl j'ai travillé:

## Le fichier entete
```md
```cpp
#pragma once

#ifdef TEST_HPP



class calculatrice{
    public:
        int add(int a, int b);
        int sub(int a, int b);
        int mul(int a, int b);
};
#else

class calculatrice{
};

#endif 
```

## le fichier calculatrice
```md
```cpp
#include "test.hpp"
#ifdef TEST_HPP

int calculatrice::add(int a, int b) {
    return a + b;
}
int calculatrice::sub(int a, int b) {
    return a - b;
}
int calculatrice::mul(int a, int b) {
    return a * b;
}
#endif 
```

## Le fichier main
```md
```cpp
#include <iostream>
#include "test.hpp"


int main() {
    calculatrice calc;
    std::cout << "Addition: " << calc.add(5, 3) << std::endl;
    std::cout << "Subtraction: " << calc.sub(5, 3) << std::endl;
    std::cout << "Multiplication: " << calc.mul(5, 3) << std::endl;
    return 0;
}
```
Apres la premiere compilation qui emploi define via la commande *g++ -DTEST_HPP main.cpp calculatrice.cpp  -o ./main*, j'obtient le resultat suivant
```md
```bash
Addition: 8
Subtraction: 2
Multiplication: 15
```

Pour la deuxieme execution sans l'emploi de define via la comande *g++ main.cpp calculatrice.cpp  -o ./main*
j'ai obtenu le resultat suivant 
```md
```bash
main.cpp:7:39: error: no member named 'add' in 'calculatrice'
    std::cout << "Addition: " << calc.add(5, 3) << std::endl;
                                 ~~~~ ^
main.cpp:8:42: error: no member named 'sub' in 'calculatrice'
    std::cout << "Subtraction: " << calc.sub(5, 3) << std::endl;
                                    ~~~~ ^
main.cpp:9:45: error: no member named 'mul' in 'calculatrice'
    std::cout << "Multiplication: " << calc.mul(5, 3) << std::endl;
                                       ~~~~ ^
3 errors generated.
```

Sans cet exercice, j'aurais su diagnostiquer le problème de manière générale, mais cet exercice m'a permis de comprendre précisément comment un #define peut modifier le contenu d'un fichier d'en-tête et provoquer une erreur dans mon propre programme.
