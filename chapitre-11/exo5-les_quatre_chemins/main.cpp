#include <iostream>
#include <string>

int main() {
    int k; if (!(std::cin >> k) || k < 0) return 0;
    if (k == 0) { std::cout << "AUCUNE MACHINE\n"; return 0; }
    for (int i = 1; i <= k; ++i) {
        std::string d, v, l, r, b, g; std::cin >> d >> v >> l >> r >> b >> g;
        int loaded = 0, released = 0;
        bool entry = false; std::string source;
        if (d == "SIMULATEUR") {
            std::cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        } else {
            if (v != "-") {
                if (v == "ABSENT") std::cout << i << " VARIABLE IGNOREE\n";
                else { ++loaded; std::cout << i << " VARIABLE CHARGEE\n"; if (v == "BON") { entry = true; source = "VARIABLE"; } else { ++released; std::cout << i << " SANS_ENTREE\n"; } }
            }
            if (!entry && loaded == 0) {
                if (l == "ABSENT") std::cout << i << " LOADER ABSENT\n";
                else { ++loaded; std::cout << i << " LOADER CHARGE\n"; if (l == "BON") { entry = true; source = "LOADER"; } else { ++released; std::cout << i << " SANS_ENTREE\n"; } }
            }
            if (!entry) {
                std::cout << i << " DIRECT " << r << '\n';
                if (r == "BON" || r == "NEGO_KO") {
                    ++loaded;
                    if (r == "BON") { entry = true; source = "DIRECT"; }
                    else { ++released; }
                }
            }
            if (!entry) {
                std::cout << i << " BACKEND INDISPONIBLE\n";
                if (loaded > released) ++released;
            } else {
                std::cout << i << " BACKEND OPENXR " << source << '\n';
                if (b == "NON") { std::cout << i << " LIAISON ECHOUEE\n"; ++released; }
            }
        }
        if (d == "OPENXR" && entry && b == "OUI") std::cout << i << " NIVEAU 1 CASQUE\n";
        else if (g == "OUI") std::cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        else std::cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";
        std::cout << i << " CHARGEES " << loaded << " LIBEREES " << released << '\n';
    }
    return 0;
}
