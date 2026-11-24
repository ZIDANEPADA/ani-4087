#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long hz, ipd, n;
    if (!(cin >> hz >> ipd >> n)) return 0;

    long long x, y, z, k0, dk, vx;
    cin >> x >> y >> z >> k0 >> dk >> vx;

    if (hz <= 1) hz = 72;
    const long long periode = 1000000000LL / hz;
    const long long demiIpd = ipd / 2;

    cout << "PERIODE " << periode << '\n';

    for (long long t = 1; t <= n; ++t) {
        const long long pas = t - 1;
        const long long lacet = ((k0 + pas * dk) % 4 + 4) % 4;
        const long long hx = x + pas * vx;
        long long dx = 0;
        long long dz = 0;

        if (lacet == 0) dx = 1;
        else if (lacet == 1) dz = -1;
        else if (lacet == 2) dx = -1;
        else dz = 1;

        const long long gx = hx - demiIpd * dx;
        const long long gz = z - demiIpd * dz;
        const long long droiteX = hx + demiIpd * dx;
        const long long droiteZ = z + demiIpd * dz;
        const long long instant = t * periode;

        cout << t << " G " << gx << ' ' << y << ' ' << gz
             << " D " << droiteX << ' ' << y << ' ' << droiteZ
             << " I " << instant << '\n';
    }
    return 0;
}
