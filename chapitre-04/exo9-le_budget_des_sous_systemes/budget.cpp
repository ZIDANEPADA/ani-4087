#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

using U32 = uint32_t;

U32 drapeau(const string& nom) {
    if (nom == "RENDER2D") return 1u;
    if (nom == "RENDER3D") return 2u;
    if (nom == "TEXT") return 4u;
    if (nom == "UI") return 8u;
    if (nom == "SHADOW") return 16u;
    if (nom == "POST_PROCESS") return 32u;
    if (nom == "ALL") return 0xFFFFFFFFu;
    return 0u;
}

long long mediane(vector<long long> v) {
    sort(v.begin(), v.end());
    return (v[4] + v[5]) / 2;
}

long long moyenne(const vector<long long>& v) {
    long long somme = 0;
    for (long long x : v)
        somme += x;
    return somme / 10;
}

int main() {
    string nom1, nom2;
    int k1, k2;

    cin >> nom1 >> k1;
    U32 value1 = 0;
    for (int i = 0; i < k1; ++i) {
        string d;
        cin >> d;
        value1 |= drapeau(d);
    }

    vector<long long> t1(10);
    for (long long& x : t1)
        cin >> x;

    cin >> nom2 >> k2;
    U32 value2 = 0;
    for (int i = 0; i < k2; ++i) {
        string d;
        cin >> d;
        value2 |= drapeau(d);
    }

    vector<long long> t2(10);
    for (long long& x : t2)
        cin >> x;

    long long med1 = mediane(t1);
    long long med2 = mediane(t2);
    long long moy1 = moyenne(t1);
    long long moy2 = moyenne(t2);

    cout << nom1 << " VALEUR " << static_cast<unsigned long long>(value1) << '\n';
    cout << nom1 << " MEDIANE " << med1 << '\n';
    cout << nom1 << " MOYENNE " << moy1 << '\n';

    cout << nom2 << " VALEUR " << static_cast<unsigned long long>(value2) << '\n';
    cout << nom2 << " MEDIANE " << med2 << '\n';
    cout << nom2 << " MOYENNE " << moy2 << '\n';

    cout << "ECART MEDIANES " << med1 - med2 << '\n';
    cout << "ECART MOYENNES " << moy1 - moy2 << '\n';
}
