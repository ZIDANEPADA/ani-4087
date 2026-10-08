#include <iostream>
#include <string>

using namespace std;

long long PoserAuSol(long long x, long long sy, long long z) {
    return sy / 2;
}

long long PoserSurTable(long long H, long long sy) {
    return H + sy / 2;
}

int main() {
    long long L, P, H, ep, pied, tx, tz;
    cin >> L >> P >> H >> ep >> pied >> tx >> tz;

    cout << "PLATEAU "
         << tx << ' ' << H - ep / 2 << ' ' << tz << '\n';

    long long hauteur_pied = H - ep;
    long long dx = L / 2 - pied;
    long long dz = P / 2 - pied;

    const long long px[4] = {-dx, dx, -dx, dx};
    const long long pz[4] = {-dz, -dz, dz, dz};

    for (int i = 0; i < 4; ++i) {
        cout << "PIED " << tx + px[i] << ' '
             << PoserAuSol(0, hauteur_pied, 0) << ' '
             << tz + pz[i] << '\n';
    }

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string nom, ou;
        long long sx, sy, sz, x, z;

        cin >> nom >> sx >> sy >> sz >> x >> z >> ou;

        long long y;
        if (ou == "SOL")
            y = PoserAuSol(x, sy, z);
        else
            y = PoserSurTable(H, sy);

        cout << nom << ' ' << x << ' ' << y << ' ' << z << '\n';
    }
}