#include <iostream>
#include <cmath>
using namespace std;
int main() {
    long long N, d; cin >> N >> d;
    long long sommePosition = 0, sommeAngle = 0;
    for (long long t = 1; t <= N; ++t) {
        long long x1, z1, a1, x2, z2, a2;
        cin >> x1 >> z1 >> a1 >> x2 >> z2 >> a2;
        long long dx = x2 - x1, dz = z2 - z1;
        long long position = llround(sqrt(static_cast<long double>(dx) * dx + static_cast<long double>(dz) * dz));
        long long angle = llabs(a2 - a1);
        sommePosition += position; sommeAngle += angle;
        cout << t << " POSITION " << position << " ANGLE " << angle << '\n';
    }
    if (N == 0 || d == 0) { cout << "AUCUNE\n"; return 0; }
    cout << "MOYENNE POSITION " << sommePosition / N << '\n'
         << "MOYENNE ANGLE " << sommeAngle / N << '\n'
         << "VITESSE " << sommeAngle / (N * d) << '\n';
    return 0;
}
