#include <iostream>
#include <string>
using namespace std;
int main() {
    int t; if (!(cin >> t)) return 0;
    string states; if (t > 0) cin >> states;
    int previous = 0, heldWith = 0, heldWithout = 0, fallen = 0;
    int takesWith = 0, takesWithout = 0, falls = 0, stuck = 0, differences = 0;
    for (int i = 0; i < t; ++i) {
        char s = states[static_cast<size_t>(i)];
        int active = s == 'x' ? 0 : 1;
        int current = s == '1' ? 1 : 0;
        int changed = current != previous ? 1 : 0;
        if (active) {
            if (current && changed) { heldWith = 1; ++takesWith; }
            else if (!current && changed) heldWith = 0;
        }
        if (!fallen) {
            if (current && changed) { heldWithout = 1; ++takesWithout; }
            else if (!current && changed) {
                if (!active && heldWithout) { heldWithout = 0; fallen = 1; ++falls; }
                else heldWithout = 0;
            }
        }
        if (s == '0' && heldWith) ++stuck;
        if (heldWith != heldWithout) ++differences;
        cout << i + 1 << ' ' << (heldWith ? "TENU" : "LIBRE") << ' ' << (heldWithout ? "TENU" : "LIBRE") << '\n';
        previous = current;
    }
    cout << "PRISES AVEC " << takesWith << '\n' << "PRISES SANS " << takesWithout << '\n'
         << "CHUTES SANS " << falls << '\n' << "COINCES AVEC " << stuck << '\n'
         << "DIFFERENCES " << differences << '\n';
}
