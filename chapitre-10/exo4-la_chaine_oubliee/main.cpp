#include <iostream>
#include <string>
using namespace std;

int main() {
    int K, N;
    cin >> K >> N;
    bool ouverte = false;
    bool emprunteeG = false, emprunteeD = false;
    int indexG = 0, indexD = 0;
    int journal = 0, avertissements = 0, silencieux = 0;
    for (int i = 1; i <= N; ++i) {
        string op;
        cin >> op;
        cout << i << ' ' << op;
        if (op == "wait") {
            if (ouverte) { cout << " REFUSE\n"; ++journal; }
            else cout << " OK\n";
        } else if (op == "begin") {
            if (ouverte) { cout << " REFUSE\n"; ++journal; }
            else { ouverte = true; cout << " OK\n"; }
        } else if (op == "acquire") {
            string oeil; cin >> oeil;
            bool &empruntee = (oeil == "G" ? emprunteeG : emprunteeD);
            int index = (oeil == "G" ? indexG : indexD);
            if (empruntee) { cout << " REFUSE\n"; ++silencieux; }
            else { empruntee = true; cout << " OK " << index << '\n'; }
        } else if (op == "release") {
            string oeil; cin >> oeil;
            bool &empruntee = (oeil == "G" ? emprunteeG : emprunteeD);
            int &index = (oeil == "G" ? indexG : indexD);
            if (!empruntee) { cout << " REFUSE\n"; ++silencieux; }
            else { empruntee = false; index = (index + 1) % K; cout << " OK\n"; }
        } else if (op == "end") {
            string g; cin >> g;
            if (g == "-") {
                if (!ouverte) { cout << " REFUSE AUCUNE\n"; ++journal; }
                else { ouverte = false; cout << " OK\n"; }
            } else {
                string d; cin >> d;
                if (!ouverte) { cout << " REFUSE AUCUNE\n"; ++journal; }
                else {
                    ouverte = false;
                    if (g == "1" && emprunteeG) { cout << " REFUSE ACQUISE G\n"; ++journal; }
                    else if (d == "1" && emprunteeD) { cout << " REFUSE ACQUISE D\n"; ++journal; }
                    else {
                        cout << " OK";
                        if (g == "0") { cout << " AVERT G"; ++avertissements; }
                        if (d == "0") { cout << " AVERT D"; ++avertissements; }
                        cout << '\n';
                    }
                }
            }
        }
    }
    cout << "JOURNAL " << journal << '\n'
         << "AVERTISSEMENTS " << avertissements << '\n'
         << "SILENCIEUX " << silencieux << '\n';
    return 0;
}
