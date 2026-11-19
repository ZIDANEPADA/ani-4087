#include <iostream>
#include <cmath>
#include <string>
using namespace std;

struct Pose { long long x, y, z; int k; };
void tourner(long long x, long long z, int k, long long &rx, long long &rz) {
    if (k == 0) { rx = x; rz = z; }
    else if (k == 1) { rx = z; rz = -x; }
    else if (k == 2) { rx = -x; rz = -z; }
    else { rx = -z; rz = x; }
}
Pose composer(const Pose &a, const Pose &p) {
    long long rx, rz; tourner(p.x, p.z, a.k, rx, rz);
    return {a.x + rx, a.y + p.y, a.z + rz, (a.k + p.k) % 4};
}
int main() {
    Pose ancre; cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k;
    long long ex, ey, ez; cin >> ex >> ey >> ez;
    int N; cin >> N;
    for (int i = 1; i <= N; ++i) {
        string espace; Pose p; long long w, h;
        cin >> espace >> p.x >> p.y >> p.z >> p.k >> w >> h;
        bool local = (espace == "L" || espace == "-");
        Pose centre = local ? composer(ancre, p) : p;
        cout << "PANNEAU " << i << ' ' << (local ? "LOCAL" : "STAGE") << '\n';
        const long long xs[4] = {-w / 2, w / 2, w / 2, -w / 2};
        const long long ys[4] = {-h / 2, -h / 2, h / 2, h / 2};
        for (int j = 0; j < 4; ++j) {
            long long rx, rz; tourner(xs[j], 0, centre.k, rx, rz);
            cout << centre.x + rx << ' ' << centre.y + ys[j] << ' ' << centre.z + rz << '\n';
        }
        long double dx = static_cast<long double>(centre.x - ex);
        long double dy = static_cast<long double>(centre.y - ey);
        long double dz = static_cast<long double>(centre.z - ez);
        cout << "DISTANCE " << llround(sqrt(dx * dx + dy * dy + dz * dz)) << '\n';
    }
    cout << "PANNEAUX " << N << '\n';
    return 0;
}
