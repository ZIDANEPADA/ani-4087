#include <iostream>
#include <iomanip>

using namespace std;

struct Dimensions {
    double largeur;
    double profondeur;
    double hauteurPlafond;
    double hauteurPorte;
    double hauteurTable;
};

int main() {
    // Dimensions de référence, reprises des ordres de grandeur du chapitre 2
    Dimensions salle = {
        4.00,  // largeur, en mètres
        3.00,  // profondeur
        2.50,  // hauteur de plafond
        2.00,  // hauteur de porte
        0.75   // hauteur de table
    };

    double facteur;
    cout << "Facteur d'echelle : ";
    cin >> facteur;

    cout << fixed << setprecision(2);
    cout << "\nDimensions affichees (echelle appliquee, valeur cachee a l'utilisateur) :\n";
    cout << "Largeur de la salle : " << salle.largeur * facteur << " m\n";
    cout << "Profondeur de la salle : " << salle.profondeur * facteur << " m\n";
    cout << "Hauteur de plafond : " << salle.hauteurPlafond * facteur << " m\n";
    cout << "Hauteur de porte : " << salle.hauteurPorte * facteur << " m\n";
    cout << "Hauteur de table : " << salle.hauteurTable * facteur << " m\n";

    return 0;
}