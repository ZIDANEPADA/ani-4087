Résultats
- Pire image : 73,7 ms
- Dépassements de 11 ms : 1000 / 1000 — c'est-à-dire toutes les images, sans exception.

Interprétation

Ce programme ne tiendrait absolument pas dans un casque. Le budget total (matériel + code) est de 20 ms, et La seule boucle de calcul en prend déjà 73,7 ms dans le pire cas. Presque 4 fois le budget total, rien que pour une opération artificielle sans aucun vrai rendu.

Et surtout, ce n'est pas un cas isolé : 1000 images sur 1000 dépassent le seuil. Ce n'est pas "une image sur cent qui prend le double" comme le dit le chapitre. C'est un dépassement systématique, à chaque image, sans exception. Un casque afficherait une image déformée et réaffichée en boucle, en continu : l'expérience serait inutilisable dès la première seconde.