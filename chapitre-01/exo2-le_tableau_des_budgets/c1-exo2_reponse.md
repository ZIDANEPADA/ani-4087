|                    Etapes    |                           valeurs trouvée |                      sources officielle  |
|------------------------------|-------------------------------------------|------------------------------------------|
| Capteurs mesurent le mouvement| **≈ 2 ms** |Blog technique officiel Meta/Oculus, "Building a Sensor for Low Latency VR" |
| Transmission de la mesure |**0,125 à 1 ms (limite protocolaire)**| Documentation officielle Microsoft (implémentant la spec USB 2.0)|
|Application décide et dessine | **Introuvable comme constante officielle**| - |
| Compositeur assemble | **Quelques millisecondes (non chiffré précisément)** | Documentation développeur officielle Meta, OS Compositor|
| Écran affiche la ligne | **Balayage à ≈ 120 lignes/ms** | Documentation développeur officielle Meta/Oculus, TimeWarp Overview |