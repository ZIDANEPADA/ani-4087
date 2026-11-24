#include <iostream>
#include <string>
using namespace std;
int main() {
    int t; if (!(cin >> t)) return 0;
    string states; if (t > 0) cin >> states;
    int previous = 0, presses = 0, releases = 0, falseReleases = 0, heldFrames = 0;
    for (int i = 0; i < t; ++i) {
        char state = states[static_cast<size_t>(i)];
        int active = state == 'x' ? 0 : 1;
        int current = state == '1' ? 1 : 0;
        int changed = current != previous ? 1 : 0;
        if (current && changed) ++presses;
        if (!current && changed) { ++releases; if (!active) ++falseReleases; }
        if (current) ++heldFrames;
        cout << i + 1 << ' ' << current << ' ' << changed << ' ' << active << '\n';
        previous = current;
    }
    cout << "APPUIS " << presses << '\n' << "RELACHES " << releases << '\n'
         << "FAUX RELACHES " << falseReleases << '\n' << "TENUES " << heldFrames << '\n';
}
