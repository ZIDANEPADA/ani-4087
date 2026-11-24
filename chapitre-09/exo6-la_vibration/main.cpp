#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;
int main() {
    int n; if (!(cin >> n)) return 0;
    long long good = 0, longCount = 0, mute = 0, totalTime = 0;
    for (int i = 1; i <= n; ++i) {
        long long a, d, f; cin >> a >> d >> f;
        long long amplitude = max(0LL, min(100LL, a));
        cout << i << ' ' << amplitude << ' ';
        if (d > 0) { cout << d; totalTime += d; } else cout << "MIN";
        cout << ' ';
        if (f > 0) cout << f; else cout << "DEFAUT";
        string verdict;
        if (amplitude == 0) { verdict = "MUETTE"; ++mute; }
        else if (d < 50) verdict = "BREVE";
        else if (d <= 200) { verdict = "BONNE"; ++good; }
        else { verdict = "LONGUE"; ++longCount; }
        cout << ' ' << verdict << '\n';
    }
    cout << "BONNES " << good << '\n' << "LONGUES " << longCount << '\n'
         << "MUETTES " << mute << '\n' << "TEMPS " << totalTime << '\n';
}
