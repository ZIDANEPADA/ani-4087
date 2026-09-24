#include <iostream>
#include <chrono>

int main()
{
volatile double  resultat  = 0.0;
const long long iterations = 500000000;
auto debut = std::chrono::high_resolution_clock::now();
for(long long i = 0; i < iterations; i ++){
    resultat += (1 % 1000)*0.000001;
}
auto fin = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> duree = fin - debut;
std::cout<< "Resultat : "<<resultat<<std::endl;
std::cout<< "Temps : " << duree.count() << "secondes" << std::endl;

    return 0;
}