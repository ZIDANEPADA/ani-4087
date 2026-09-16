#include <chrono>
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    const int NB_IMAGES = 1000;
    const double SEUIL_MS = 11.0;

    std::vector<double> durees;
    durees.reserve(NB_IMAGES);

    for (int i = 0; i < NB_IMAGES; ++i) {
        auto t1 = std::chrono::high_resolution_clock::now();

        // Le "rendu" simulé : un calcul volontairement coûteux
        volatile double somme = 0.0;
        for (int k = 0; k < 500000; ++k) {
            somme += std::sin(k) * std::cos(k);
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        double dureeMs = std::chrono::duration<double, std::milli>(t2 - t1).count();

        durees.push_back(dureeMs); // ← la ligne qui manquait
    }

    double pire = 0.0;
    int nbDepassements = 0;
    for (double d : durees) {
        if (d > pire) pire = d;
        if (d > SEUIL_MS) nbDepassements++;
    }

    std::cout << "Pire image : " << pire << " ms\n";
    std::cout << "Images > " << SEUIL_MS << " ms : "
              << nbDepassements << " / " << durees.size() << "\n";

    return 0;
}