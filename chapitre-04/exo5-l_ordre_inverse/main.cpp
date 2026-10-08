#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int deplaces = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        string nom;
        long long tx, ty, tz, sx, sy, sz;
        cin >> nom >> tx >> ty >> tz >> sx >> sy >> sz;

        long long x = (sx * tx) / 1000;
        long long y = (sy * ty) / 1000;
        long long z = (sz * tz) / 1000;

        long long ex = llabs(tx - x);
        long long ey = llabs(ty - y);
        long long ez = llabs(tz - z);
        long long ecart = max(ex, max(ey, ez));

        cout << nom << ' ' << x << ' ' << y << ' ' << z
             << ' ' << ecart << '\n';

        if (ecart != 0)
            ++deplaces;

        pire = max(pire, ecart);
    }

    cout << "DEPLACES " << deplaces << '\n';
    cout << "PIRE " << pire << '\n';
}
