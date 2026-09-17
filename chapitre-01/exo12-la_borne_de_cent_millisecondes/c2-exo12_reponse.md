chapitre-01/exo12-la_borne_de_cent_millisecondes/Figure_1.png

La courbe montre que l'erreur d'extrapolation varie avec la durée de prédiction. Elle augmente jusqu'à environ 3°, puis diminue presque jusqu'à 0°, avant de remonter à nouveau. ça signifie que plus on cherche à prédire la pose de la tête longtemps à l'avance, plus l'extrapolation peut devenir imprécise.

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {

    const double vitesse_estimee = 180.0; 

    ofstream fichier("erreur.csv");

    fichier << "duree_ms,pose_predite,pose_reelle,erreur\n";


    double pose_reelle = 0.0;


    for (int t = 10; t <= 1000; t += 10) {

   
        double temps = t / 1000.0;



        double pose_predite = vitesse_estimee * temps;




        double vitesse_reelle =
            180.0 + 30.0 * sin(t * 0.02);


        pose_reelle += vitesse_reelle * 0.010;




        double erreur = abs(pose_predite - pose_reelle);



        cout << t << " ms"
             << " | Predite = " << pose_predite
             << " deg"
             << " | Reelle = " << pose_reelle
             << " deg"
             << " | Erreur = " << erreur
             << " deg"
             << endl;


        // Enregistrement dans le CSV
        fichier << t << ","
                << pose_predite << ","
                << pose_reelle << ","
                << erreur << "\n";
    }

    fichier.close();

    cout << "\nLes resultats ont ete enregistres dans erreur.csv" << endl;

    return 0;
}




import pandas as pd
import matplotlib.pyplot as plt

# Lire le fichier créé par C++
data = pd.read_csv("erreur.csv")

# Tracer l'erreur
plt.plot(data["duree_ms"], data["erreur"])

# Ligne verticale à 100 ms
plt.axvline(100, linestyle="--")

plt.xlabel("Duree d'extrapolation (ms)")
plt.ylabel("Erreur (degres)")
plt.title("Erreur d'extrapolation de la pose de tete")

plt.grid()
plt.show()