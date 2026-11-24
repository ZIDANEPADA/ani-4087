#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long hz;
    if (!(cin >> hz)) return 0;

    string ligne;
    getline(cin, ligne);
    getline(cin, ligne);

    long long pose[5] = {0, 0, 0, 1700, 0};
    if (ligne.rfind("FIXE", 0) == 0) {
        istringstream flux(ligne.substr(4));
        for (long long& valeur : pose) flux >> valeur;
    }

    int t;
    cin >> t;
    vector<long long> a(t), b(t);
    for (int i = 0; i < t; ++i) cin >> a[i];
    for (int i = 0; i < t; ++i) cin >> b[i];

    if (hz <= 1) hz = 72;
    const long long periode = 1000000000LL / hz;

    cout << "PERIODE " << periode << '\n';
    cout << "POSE";
    for (long long valeur : pose) cout << ' ' << valeur;
    cout << '\n';

    int premierBrut = 0;
    int premierRelatif = 0;
    for (int i = 0; i < t; ++i) {
        long long brut = b[i] - a[i];
        long long relatif = (b[i] - b[0]) - (a[i] - a[0]);
        long long scripte = static_cast<long long>(i + 1) * periode;
        cout << i + 1 << " BRUT " << brut
             << " RELATIF " << relatif
             << " SCRIPTE " << scripte << '\n';
        if (brut != 0 && premierBrut == 0) premierBrut = i + 1;
        if (relatif != 0 && premierRelatif == 0) premierRelatif = i + 1;
    }

    if (premierBrut == 0) cout << "BRUT IDENTIQUE\n";
    else cout << "BRUT DIFFERENT " << premierBrut << '\n';
    if (premierRelatif == 0) cout << "RELATIF IDENTIQUE\n";
    else cout << "RELATIF DIFFERENT " << premierRelatif << '\n';
    return 0;
}
