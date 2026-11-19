#include <iostream>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T;
    int justes = 0, fautives = 0;
    for (int t = 1; t <= T; ++t) {
        int n;
        cin >> n;
        bool wait = false, begin = false, vues = false;
        bool gauche = false, droite = false, end = false;
        string faute;
        int position = 0;
        for (int p = 1; p <= n; ++p) {
            string appel;
            cin >> appel;
            if (!faute.empty()) continue;
            if (end) { faute = "APRES_END"; position = p; }
            else if (appel == "WAIT") {
                if (begin) { faute = "WAIT_APRES_BEGIN"; position = p; }
                else wait = true;
            } else if (appel == "BEGIN") {
                if (begin) { faute = "DOUBLE_BEGIN"; position = p; }
                else if (!wait) { faute = "BEGIN_SANS_WAIT"; position = p; }
                else begin = true;
            } else if (appel == "VUES") {
                if (!wait) { faute = "VUES_SANS_WAIT"; position = p; }
                else vues = true;
            } else if (appel == "PREND_G" || appel == "PREND_D") {
                if (!begin) { faute = "PREND_SANS_BEGIN"; position = p; }
                else if (!vues) { faute = "PREND_SANS_VUES"; position = p; }
                else if (appel == "PREND_G" ? gauche : droite) { faute = "DOUBLE_PREND"; position = p; }
                else if (appel == "PREND_G") gauche = true;
                else droite = true;
            } else if (appel == "LACHE_G" || appel == "LACHE_D") {
                if (appel == "LACHE_G") {
                    if (!gauche) { faute = "LACHE_SANS_PREND"; position = p; }
                    else gauche = false;
                } else {
                    if (!droite) { faute = "LACHE_SANS_PREND"; position = p; }
                    else droite = false;
                }
            } else if (appel == "END") {
                if (!begin) { faute = "END_SANS_BEGIN"; position = p; }
                else if (gauche || droite) { faute = "END_IMAGE_PRISE"; position = p; }
                else end = true;
            }
        }
        if (faute.empty() && !end) { faute = "SANS_END"; position = n + 1; }
        if (faute.empty()) { cout << t << " OK\n"; ++justes; }
        else { cout << t << " FAUTE " << position << ' ' << faute << '\n'; ++fautives; }
    }
    cout << "JUSTES " << justes << '\n' << "FAUTIVES " << fautives << '\n';
    return 0;
}
