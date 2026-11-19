#include <iostream>
#include <string>
using namespace std;

int main() {
    string politique;
    int T;
    cin >> politique >> T;
    string signes;
    if (T > 0) cin >> signes;
    bool ouverte = false;
    int rendues = 0, perdues = 0, erreurs = 0, premierRefus = 0;
    for (int t = 1; t <= T; ++t) {
        bool rendre = false;
        bool waitOK = !ouverte;
        if (!waitOK) {
            ++erreurs;
            if (premierRefus == 0) premierRefus = t;
        } else {
            rendre = signes[t - 1] == '1';
        }
        bool beginOK = !ouverte;
        if (!beginOK) ++erreurs;
        else ouverte = true;
        if (rendre) ++rendues;
        else if (signes[t - 1] == '1') ++perdues;
        bool appelerEnd = (politique == "TOUJOURS") || rendre;
        string endResultat = "-";
        if (appelerEnd) {
            if (ouverte) { ouverte = false; endResultat = "OK"; }
            else { ++erreurs; endResultat = "REFUSE"; }
        }
        cout << t << ' ' << (waitOK ? "OK" : "REFUSE") << ' '
             << (beginOK ? "OK" : "REFUSE") << ' '
             << (rendre ? "OUI" : "NON") << ' ' << endResultat << '\n';
    }
    cout << "RENDUES " << rendues << '\n'
         << "PERDUES " << perdues << '\n'
         << "ERREURS " << erreurs << '\n'
         << "PREMIER REFUS " << (premierRefus == 0 ? "AUCUN" : to_string(premierRefus)) << '\n';
    return 0;
}
