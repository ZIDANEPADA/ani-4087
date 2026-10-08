#include <iostream>
#include <string>

using namespace std;

int main() {
    long long W, H, seuil;
    cin >> W >> H >> seuil;

    int n;
    cin >> n;

    int ok = 0;
    int a_reprendre = 0;

    for (int i = 0; i < n; ++i) {
        string nom;
        long long u, y, l, h, e, d;
        cin >> nom >> u >> y >> l >> h >> e >> d;

        long long xmin = u - l / 2;
        long long xmax = u + l / 2;
        long long ymin = y - h / 2;
        long long ymax = y + h / 2;

        long long saillie = d + e / 2;
        long long arriere = d - e / 2;

        string verdict;

        if (xmin < -W / 2 || xmax > W / 2 ||
            ymin < 0 || ymax > H) {
            verdict = "DEBORDE";
        } else if (saillie <= 0) {
            verdict = "INVISIBLE";
        } else if (saillie < seuil) {
            verdict = "CLIGNOTE";
        } else if (arriere > seuil) {
            verdict = "DECOLLE";
        } else {
            verdict = "OK";
        }

        cout << nom << ' ' << saillie << ' ' << verdict << '\n';

        if (verdict == "OK")
            ++ok;
        else
            ++a_reprendre;
    }

    cout << "OK " << ok << '\n';
    cout << "A REPRENDRE " << a_reprendre << '\n';
}
