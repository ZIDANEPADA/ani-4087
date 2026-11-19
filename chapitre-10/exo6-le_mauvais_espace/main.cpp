#include <iostream>
using namespace std;

struct Pose { long long x, y, z; int k; };

Pose composer(const Pose &a, const Pose &p) {
    long long x = p.x, z = p.z;
    if (a.k == 1) { x = p.z; z = -p.x; }
    else if (a.k == 2) { x = -p.x; z = -p.z; }
    else if (a.k == 3) { x = -p.z; z = p.x; }
    return {a.x + x, a.y + p.y, a.z + z, (a.k + p.k) % 4};
}

int main() {
    Pose ancre;
    cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k;
    int N; cin >> N;
    int justes = 0, fausses = 0;
    for (int i = 1; i <= N; ++i) {
        char D, C; Pose p;
        cin >> D >> C >> p.x >> p.y >> p.z >> p.k;
        Pose vraie = (D == 'L') ? composer(ancre, p) : p;
        Pose crue = (C == 'L') ? composer(ancre, p) : p;
        long long dx = crue.x - vraie.x;
        long long dy = crue.y - vraie.y;
        long long dz = crue.z - vraie.z;
        int dk = (crue.k - vraie.k + 4) % 4;
        cout << i << " CRU " << crue.x << ' ' << crue.y << ' ' << crue.z << ' ' << crue.k << '\n';
        cout << i << " ECART " << dx << ' ' << dy << ' ' << dz << ' ' << dk << '\n';
        if (dx == 0 && dy == 0 && dz == 0 && dk == 0) ++justes;
        else ++fausses;
    }
    cout << "JUSTES " << justes << '\n' << "FAUSSES " << fausses << '\n';
    return 0;
}
