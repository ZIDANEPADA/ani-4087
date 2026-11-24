#include <iostream>
#include <vector>
#include <limits>
using namespace std;
struct Pose { long long x, y; int k; };
Pose compose(const Pose& a, const Pose& b) {
    long long rx = b.x, ry = b.y;
    if (a.k == 1) { rx = -b.y; ry = b.x; }
    else if (a.k == 2) { rx = -b.x; ry = -b.y; }
    else if (a.k == 3) { rx = b.y; ry = -b.x; }
    return {a.x + rx, a.y + ry, (a.k + b.k) % 4};
}
Pose inversePose(const Pose& a) {
    int angle = (4 - a.k) % 4;
    return compose({0, 0, angle}, {-a.x, -a.y, 0});
}
int main() {
    int m, t; if (!(cin >> m >> t)) return 0;
    vector<Pose> objects(static_cast<size_t>(m));
    for (auto& object : objects) cin >> object.x >> object.y >> object.k;
    int held = -1, previousButton = 0, takes = 0, misses = 0;
    Pose attachment{0, 0, 0};
    for (int frame = 1; frame <= t; ++frame) {
        Pose palm; int button; cin >> palm.x >> palm.y >> palm.k >> button;
        bool pressed = button == 1 && previousButton == 0;
        bool released = button == 0 && previousButton == 1;
        bool missed = false;
        if (released) held = -1;
        if (pressed) {
            long long bestDistance = numeric_limits<long long>::max();
            int best = -1;
            for (int j = 0; j < m; ++j) {
                long long dx = objects[static_cast<size_t>(j)].x - palm.x;
                long long dy = objects[static_cast<size_t>(j)].y - palm.y;
                long long distance = dx * dx + dy * dy;
                if (distance <= 22500 && distance < bestDistance) { bestDistance = distance; best = j; }
            }
            if (best >= 0) {
                held = best;
                Pose inv{0, 0, 0};
                int angle = (4 - palm.k) % 4;
                long long nx = -palm.x, ny = -palm.y, rx = nx, ry = ny;
                if (angle == 1) { rx = -ny; ry = nx; }
                else if (angle == 2) { rx = -nx; ry = -ny; }
                else if (angle == 3) { rx = ny; ry = -nx; }
                inv = {rx, ry, angle};
                attachment = compose(inv, objects[static_cast<size_t>(best)]);
                ++takes;
            } else { missed = true; ++misses; }
        }
        if (held >= 0) {
            objects[static_cast<size_t>(held)] = compose(palm, attachment);
            const Pose& p = objects[static_cast<size_t>(held)];
            cout << frame << " TIENT " << held + 1 << ' ' << p.x << ' ' << p.y << ' ' << p.k << '\n';
        } else if (missed) cout << frame << " RATE\n";
        else cout << frame << " LIBRE\n";
        previousButton = button;
    }
    cout << "SAISIES " << takes << '\n' << "RATEES " << misses << '\n';
    for (int j = 0; j < m; ++j) {
        const Pose& p = objects[static_cast<size_t>(j)];
        cout << "OBJET " << j + 1 << ' ' << p.x << ' ' << p.y << ' ' << p.k << '\n';
    }
}
