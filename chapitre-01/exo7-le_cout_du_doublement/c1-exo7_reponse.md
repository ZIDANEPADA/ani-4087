L'estimation du doublement

Ce qui se double en stéréo, c'est le rendu de la scène, pas la logique, pas la physique. Donc si 73,7 ms correspond à un seul rendu, l'approximation pour deux rendus est :
73,7×2=147,4 ms

Ce qu'il resterait pour le reste

Rappel du budget total : à 90 Hz, le code dispose d'environ 11,1 ms par image 

3,1−147,4=−144,3 ms

Le résultat est massivement négatif. Concrètement : il ne reste rien, le simple fait de doubler ce calcul dépasse le budget total d'un facteur d'environ 47.

L'interprétation à écrire

Avec un rendu aussi lourd, la question, il n'y a plus de reste à distribuer, il faut d'abord réduire drastiquement le coût du rendu lui-même avant même de penser à la logique, la physique ou le chargement.

Le rendu mesuré dépasse déjà à lui seul le budget total d'une image de plus de 6 fois avant même le doublement stéréo. Doublé, il atteint environ 147 ms, soit environ 47 fois le budget réellement disponible pour le code applicatif. Ce résultat montre qu'un calcul non optimisé rend la question du partage du budget entre logique, physique et rendu totalement théorique tant que le coût du rendu lui-même n'a pas été réduit d'un ou deux ordres de grandeur.