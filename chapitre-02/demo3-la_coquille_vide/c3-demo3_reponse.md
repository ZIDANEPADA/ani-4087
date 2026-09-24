## Demonstration 3 : 
Montrez le même en-tête compilé avec et sans son define, et faites constater qu'il ne déclare pas la même classe.

Expliquez ensuite pourquoi le lieur, et non le compilateur, est celui qui proteste.

voici les fichiers avec lesquels j'ai travaillé

## module.hpp
```md
```cpp
#ifdef MODULE_ACTIVE

class Module{
    public:
        void hello();
};

#else

class Module{

};

#endif 
```
## module.cpp
```md
```cpp
#include "module.hpp"
#ifdef MODULE_ACTIVE
#include <iostream>

void Module::hello(){
    std::cout<< "Hello" << std::endl;
}

#endif
```

## main.cpp

```md
```cpp
#include "module.hpp"


int main() {
    Module module;
    module.hello();
    return 0;
}
```

Lorsque j'execute la commande *g++ -DMODULE_ACTIVE main.cpp module.cpp -o main*

j'obtient
```md
```bash
Hello
```
c'est a dire que la classe exixte

lorsque j'execute la commande   *g++ main.cpp module.cpp -o main*
j'ai directement une erreur
 ```md
 ```bash
 main.cpp:6:12: error: no member named 'hello' in 'Module'
    module.hello();
    ~~~~~~ ^
1 error generated.
```

le head peut presenter le=a coquille vide mais l'erreur apparait lorque le programeme demande *module.hello()*

le meme head change selon les define, puis l'erreur apparait au niveau du lieux.