#include "module.hpp"
#ifdef MODULE_ACTIVE
#include <iostream>

void Module::hello(){
    std::cout<< "Hello" << std::endl;
}

#endif