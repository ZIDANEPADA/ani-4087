#include <iostream>
#include <string>
using namespace std;

int main() {
    int N, T;
    cin >> N >> T;
    if (N < 1 || N > 4) {
        cout << "CHAINE REFUSEE\n";
        return 0;
    }
    string signes;
    if (T > 0) cin >> signes;
    int prochaine = 0, rendues = 0, sautees = 0;
    for (int t = 1; t <= T; ++t) {
        if (signes[t - 1] == '1') {
            cout << t << " OUI 1 " << t - 1 << ' ' << prochaine << '\n';
            prochaine = (prochaine + 1) % N;
            ++rendues;
        } else {
            cout << t << " NON 0\n";
            ++sautees;
        }
    }
    cout << "FINS " << T << '\n'
         << "RENDUES " << rendues << '\n'
         << "SAUTEES " << sautees << '\n'
         << "PROCHAINE " << prochaine << '\n';
    return 0;
}
