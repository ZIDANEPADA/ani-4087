#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Mur {
    string nom;
    long long xmin, xmax, zmin, zmax;
};

bool contient(const Mur& mur,
              long long xmin, long long xmax,
              long long zmin, long long zmax) {
    return mur.xmin <= xmin && mur.xmax >= xmax &&
           mur.zmin <= zmin && mur.zmax >= zmax;
}

int main() {
    long long L, e;
    cin >> L >> e;

    int n;
    cin >> n;

    vector<Mur> murs(n);

    for (int i = 0; i < n; ++i) {
        long long cx, cz, sx, sz;
        cin >> murs[i].nom >> cx >> cz >> sx >> sz;

        murs[i].xmin = cx - sx / 2;
        murs[i].xmax = cx + sx / 2;
        murs[i].zmin = cz - sz / 2;
        murs[i].zmax = cz + sz / 2;

        cout << murs[i].nom << ' '
             << murs[i].xmin << ' ' << murs[i].xmax << ' '
             << murs[i].zmin << ' ' << murs[i].zmax << '\n';
    }

    long long h = L / 2;

    struct Angle {
        string nom;
        long long xmin, xmax, zmin, zmax;
    };

    vector<Angle> angles = {
        {"FOND_GAUCHE", -h - e, -h, -h - e, -h},
        {"FOND_DROIT",    h, h + e, -h - e, -h},
        {"ENTREE_GAUCHE", -h - e, -h, h, h + e},
        {"ENTREE_DROIT",  h, h + e, h, h + e}
    };

    int trous = 0;

    for (const Angle& angle : angles) {
        int nb = 0;
        for (const Mur& mur : murs) {
            if (contient(mur, angle.xmin, angle.xmax,
                         angle.zmin, angle.zmax)) {
                ++nb;
            }
        }

        string verdict = (nb == 1) ? "BOUCHE" : "TROU";
        if (verdict == "TROU")
            ++trous;

        cout << angle.nom << ' ' << verdict << '\n';
    }

    cout << "TROUS " << trous << '\n';
}
