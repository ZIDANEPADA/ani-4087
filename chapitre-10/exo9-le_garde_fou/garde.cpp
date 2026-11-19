#include <iostream>
#include <string>
using namespace std;

class Session {
public:
    bool ouverte = false;
    int debuts = 0, fins = 0, refus = 0;
    bool Wait() { if (ouverte) { ++refus; return false; } return true; }
    bool Begin() { if (ouverte) { ++refus; return false; } ouverte = true; ++debuts; return true; }
    bool End() { if (!ouverte) { ++refus; return false; } ouverte = false; ++fins; return true; }
};

class GardeTrame {
    Session *session;
public:
    explicit GardeTrame(Session &s) : session(&s) {}
    GardeTrame(const GardeTrame &) = delete;
    GardeTrame &operator=(const GardeTrame &) = delete;
    ~GardeTrame() { session->End(); }
};

void executer(const string &signes, bool avecGarde) {
    Session s;
    int images = 0;
    for (char original : signes) {
        char signe = original;
        bool waitOK = s.Wait();
        if (!waitOK && (signe == 'N' || signe == 'C')) signe = 'V';
        bool beginOK = s.Begin();
        if (!beginOK && (signe == 'N' || signe == 'C')) signe = 'V';
        if (signe == 'N') ++images;

        if (avecGarde) {
            if (beginOK) {
                GardeTrame garde(s);
                if (signe == 'C') continue;
                if (signe == 'R') break;
            } else if (signe == 'R') {
                break;
            }
        } else {
            if (signe == 'C') continue;
            if (signe == 'R') break;
            s.End();
        }
    }
    cout << (avecGarde ? "AVEC" : "SANS") << " DEBUTS " << s.debuts
         << " FINS " << s.fins << " REFUS " << s.refus
         << " IMAGES " << images << " OUVERTE " << (s.ouverte ? "OUI" : "NON") << '\n';
}

int main() {
    int T; cin >> T;
    string signes; if (T > 0) cin >> signes;
    executer(signes, false);
    executer(signes, true);
    return 0;
}
