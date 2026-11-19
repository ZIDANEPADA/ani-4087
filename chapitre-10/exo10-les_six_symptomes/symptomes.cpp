#include <iostream>
#include <string>
using namespace std;
int main() {
    int N; cin >> N;
    int muettes = 0;
    for (int i = 1; i <= N; ++i) {
        string fin, instant, pose, espace;
        int g, d;
        cin >> fin >> g >> d >> instant >> pose >> espace;
        string symptomes;
        auto ajouter = [&](const string &s) { if (!symptomes.empty()) symptomes += ' '; symptomes += s; };
        if (fin == "JAMAIS") ajouter("FIGE");
        else if (fin == "SI_RENDU") ajouter("NE_REPART_PAS");
        if (g == 0) ajouter("OEIL_NOIR_G");
        if (d == 0) ajouter("OEIL_NOIR_D");
        if (instant == "N") ajouter("TREMBLE");
        if (pose == "F") ajouter("DE_TRAVERS");
        if (espace == "L") ajouter("DECALE");
        bool dit = fin != "TOUJOURS" || g == 0 || d == 0;
        cout << i << " CASQUE " << (symptomes.empty() ? "AUCUN" : symptomes) << '\n';
        cout << i << " SIMULATEUR " << (dit ? "DIT" : "MUET") << '\n';
        if (!symptomes.empty() && !dit) ++muettes;
    }
    cout << "MUETTES " << muettes << '\n';
    return 0;
}
