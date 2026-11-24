#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

long long lireNombre(const string& texte, size_t& position, bool& trouve) {
    while (position < texte.size() && isspace(static_cast<unsigned char>(texte[position]))) {
        ++position;
    }

    size_t debut = position;
    if (position < texte.size() && (texte[position] == '+' || texte[position] == '-')) {
        ++position;
    }

    size_t debutChiffres = position;
    while (position < texte.size() && isdigit(static_cast<unsigned char>(texte[position]))) {
        ++position;
    }

    trouve = position > debutChiffres;
    if (!trouve) {
        position = debut;
        return 0;
    }

    return stoll(texte.substr(debut, position - debut));
}

vector<long long> lirePose(const string& texte) {
    vector<long long> nombres;
    size_t position = 0;

    while (position < texte.size() && nombres.size() < 5) {
        bool trouve = false;
        long long valeur = lireNombre(texte, position, trouve);
        if (!trouve) {
            break;
        }
        nombres.push_back(valeur);

        while (position < texte.size() &&
               (texte[position] == ',' || isspace(static_cast<unsigned char>(texte[position])))) {
            ++position;
        }
    }
    return nombres;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string ligne;
    if (!getline(cin, ligne)) return 0;

    string backend;
    long long hz, latence;
    string demi, profondeur, liste;
    {
        istringstream flux(ligne);
        flux >> backend >> hz >> demi >> profondeur >> liste >> latence;
    }

    string loader;
    getline(cin, loader);
    if (loader.empty() && cin.good()) getline(cin, loader);

    string poseLigne;
    getline(cin, poseLigne);
    if (poseLigne.empty() && cin.good()) getline(cin, poseLigne);

    bool poseFixe = false;
    vector<long long> pose = {0, 0, 0, 1700, 0};
    if (poseLigne.rfind("FIXE", 0) == 0) {
        vector<long long> lue = lirePose(poseLigne.substr(4));
        if (lue.size() == 5) {
            pose = lue;
            poseFixe = true;
        }
    }

    int m = 0;
    cin >> m;
    getline(cin, ligne);

    int appliquees = 0;
    int ignorees = 0;
    for (int i = 0; i < m; ++i) {
        getline(cin, ligne);
        size_t egal = ligne.find('=');
        if (egal == string::npos) {
            ++ignorees;
            continue;
        }

        string nom = ligne.substr(0, egal);
        string valeur = ligne.substr(egal + 1);
        if (valeur.empty()) {
            ++ignorees;
            continue;
        }

        bool appliquee = true;
        if (nom == "NK_XR_BACKEND") {
            if (valeur == "openxr") backend = "OPENXR";
            else appliquee = false;
        } else if (nom == "NK_XR_HZ") {
            size_t p = 0;
            bool trouve = false;
            hz = lireNombre(valeur, p, trouve);
        } else if (nom == "NK_XR_SIM_LATENCY_MS") {
            size_t p = 0;
            bool trouve = false;
            latence = lireNombre(valeur, p, trouve);
        } else if (nom == "NK_XR_HALF_RATE" || nom == "NK_XR_DEPTH_LAYER" || nom == "NK_XR_LIST_EXT") {
            string resultat = (valeur[0] == '0' || valeur == "false") ? "NON" : "OUI";
            if (nom == "NK_XR_HALF_RATE") demi = resultat;
            else if (nom == "NK_XR_DEPTH_LAYER") profondeur = resultat;
            else liste = resultat;
        } else if (nom == "NK_XR_OPENXR_LOADER") {
            loader = valeur;
        } else if (nom == "NK_XR_SIM_POSE") {
            vector<long long> lue = lirePose(valeur);
            if (lue.size() == 5) {
                pose = lue;
                poseFixe = true;
            } else {
                appliquee = false;
            }
        } else {
            appliquee = false;
        }

        if (appliquee) ++appliquees;
        else ++ignorees;
    }

    cout << "BACKEND " << backend << '\n';
    cout << "HZ " << hz << '\n';
    cout << "DEMI " << demi << '\n';
    cout << "PROFONDEUR " << profondeur << '\n';
    cout << "LISTE " << liste << '\n';
    cout << "LOADER " << (loader.empty() ? "-" : loader) << '\n';
    cout << "LATENCE " << latence << '\n';
    if (poseFixe) {
        cout << "POSE FIXE";
        for (long long valeur : pose) cout << ' ' << valeur;
        cout << '\n';
    } else {
        cout << "POSE LIBRE\n";
    }
    cout << "APPLIQUEES " << appliquees << '\n';
    cout << "IGNOREES " << ignorees << '\n';
    return 0;
}
