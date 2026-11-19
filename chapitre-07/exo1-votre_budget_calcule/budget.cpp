// Sprint 7 — exo1-votre_budget_calcule
// Fichier de travail : budget.cpp
// À intégrer au projet MaSalle du kit R3D conformément à l'énoncé.
// Les fonctions NkChrono/NkQuat/NkVec du cours doivent être utilisées dans la version finale.
#include <cstdio>
#include <cmath>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

// Rappel de calcul indépendant des API du moteur.
// Ne remplace pas la boucle de rendu de MaSalle : placez la logique demandée
// dans etapes/etape5_salle.cpp / src/main.cpp comme l'indique l'énoncé.
namespace sprint7 {
constexpr double kPi = 3.14159265358979323846;
constexpr double PeriodMs(double hz) { return 1000.0 / hz; }
constexpr double ClampHorizon(double seconds) {
    return seconds < -0.1 ? -0.1 : (seconds > 0.1 ? 0.1 : seconds);
}
}

int main() {
    std::printf("Sprint 7 — exo1-votre_budget_calcule\n");
    std::printf("Périodes théoriques : 72 Hz = %.3f ms ; 90 Hz = %.3f ms ; 120 Hz = %.3f ms\n",
                sprint7::PeriodMs(72.0), sprint7::PeriodMs(90.0), sprint7::PeriodMs(120.0));
    std::printf("Intégrez la mesure spécifique dans MaSalle puis recopiez la sortie réelle dans budget.txt.\n");
    return 0;
}
