#include <iostream>
using namespace std;
int main() {
    int t; if (!(cin >> t)) return 0;
    int current = 0, changed = 0, active = 0, previousPhysical = 0;
    int realPresses = 0, grabs = 0, refused = 0;
    for (int i = 1; i <= t; ++i) {
        int p, s, focused; cin >> p >> s >> focused;
        if (p == 1 && previousPhysical == 0) ++realPresses;
        previousPhysical = p;
        for (int j = 0; j < s; ++j) {
            if (!focused) ++refused;
            else { changed = (p != current) ? 1 : 0; current = p; active = 1; }
        }
        bool grabbed = current && changed;
        if (grabbed) ++grabs;
        cout << i << ' ' << current << ' ' << changed << ' ' << active << ' ' << (grabbed ? "SAISIT" : "-") << '\n';
    }
    cout << "APPUIS REELS " << realPresses << '\n' << "SAISIES " << grabs << '\n' << "SYNC REFUSEES " << refused << '\n';
}
