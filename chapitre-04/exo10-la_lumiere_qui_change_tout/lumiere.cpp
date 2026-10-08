#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Vec3 {
    double x, y, z;
};

struct Face {
    string nom;
    Vec3 normale;
};

double longueur(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

int lumiereFace(int ambiante, Vec3 normale, Vec3 direction, int intensite) {
    double len = longueur(direction);

    double produit =
        normale.x * direction.x +
        normale.y * direction.y +
        normale.z * direction.z;

    double c = -produit / len;
    c = max(0.0, c);

    return ambiante + static_cast<int>(floor(intensite * c + 0.5));
}

int main() {
    int ambiante, n;
    cin >> ambiante >> n;

    const vector<Face> faces = {
        {"SOL",    {0, 1, 0}},
        {"FOND",   {0, 0, 1}},
        {"ENTREE", {0, 0, -1}},
        {"GAUCHE", {1, 0, 0}},
        {"DROIT",  {-1, 0, 0}}
    };

    for (int i = 0; i < n; ++i) {
        string nom;
        Vec3 direction;
        int intensite;

        cin >> nom >> direction.x >> direction.y
            >> direction.z >> intensite;

        vector<int> valeurs;

        for (const Face& face : faces) {
            int valeur = lumiereFace(
                ambiante, face.normale, direction, intensite
            );

            valeurs.push_back(valeur);
            cout << nom << ' ' << face.nom << ' '
                 << valeur << '\n';
        }

        int contraste =
            *max_element(valeurs.begin(), valeurs.end()) -
            *min_element(valeurs.begin(), valeurs.end());

        cout << nom << " CONTRASTE " << contraste << '\n';
    }
}
