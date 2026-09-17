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