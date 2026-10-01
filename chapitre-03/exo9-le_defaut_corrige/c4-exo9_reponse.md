## Exercice 9 : Le défaut corrigé

Écrivez l'accumulateur : un rappel sur NkMouseRawEvent qui ajoute, et une consommation par image qui prend le total et remet à zéro.

Reprenez la mesure de l'exercice précédent. Rendez les deux séries côte à côte.

# Reponse
```md
```bash
deltaX direct = -1 | deltaX accumule = -1
deltaX direct = -1 | deltaX accumule = -1
deltaX direct = -3 | deltaX accumule = -3
deltaX direct = -1 | deltaX accumule = -1
deltaX direct = -2 | deltaX accumule = -2
deltaX direct = -2 | deltaX accumule = -2
deltaX direct = -2 | deltaX accumule = -2
deltaX direct = -2 | deltaX accumule = -2
deltaX direct = -2 | deltaX accumule = -2
deltaX direct = -2 | deltaX accumule = -2
deltaX direct = -3 | deltaX accumule = -3
deltaX direct = -3 | deltaX accumule = -3
deltaX direct = -3 | deltaX accumule = -3
deltaX direct = -5 | deltaX accumule = -5
deltaX direct = -3 | deltaX accumule = -3
deltaX direct = -5 | deltaX accumule = -5
deltaX direct = -3 | deltaX accumule = -3
deltaX direct = -5 | deltaX accumule = -5
deltaX direct = -5 | deltaX accumule = -5
deltaX direct = -6 | deltaX accumule = -6
deltaX direct = -5 | deltaX accumule = -5
```

Ces résultats montrent que plusieurs déplacements peuvent être reçus successivement avant la consommation du total : l'accumulateur additionne les deltaX des événements, puis le total est consommé et remis à zéro pour l'image suivante.