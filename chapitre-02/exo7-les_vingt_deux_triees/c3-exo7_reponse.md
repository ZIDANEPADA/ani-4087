## Exercice 7 : 
Prenez la liste des vingt-trois dépendances de la démonstration du moteur et classez-la en trois groupes : celles dont le nom suffit à deviner le rôle, celles dont vous avez une idée sans certitude, celles dont vous ne savez rien.

Pour ce troisième groupe, ouvrez l'en-tête principal de chaque module et rendez une phrase par module.

## les 23 dependances
```md
```bash
1.  %{wks.location}/Externals
2.  %{NKGlad.location}/include
3.  %{NKEvent.location}/src
4.  %{NKWindow.location}/src
5.  %{NKLogger.location}/src
6.  %{NKCore.location}/src
7.  %{NKPlatform.location}/src
8.  %{NKMath.location}/src
9.  %{NKTime.location}/src
10. %{NKStream.location}/src
11. %{NKFileSystem.location}/src
12. %{NKMemory.location}/src
13. %{NKContainers.location}/src
14. %{NKThreading.location}/src
15. %{NKRHI.location}/src
16. %{NKSL.location}/src
17. %{NKRenderer.location}/src
18. %{NKAnima.location}/src
19. %{NKPhysics.location}/src
20. %{NKCollision.location}/src
21. %{NKSerialization.location}/src
22. %{NKReflection.location}/src
23. %{NKMedia.location}/src
```
elles designent en grande partie les fondations qui étaient auparavant utilisées indirectement sans être nommées explicitement.

## Groupe 1 - Le nom suffit à deviner le role
1. %{NKEvent.location}/src : gestion des evenements
2. %{NKWindow.location}/src : gestion des fenetres
3. %{NKLogger.location}/src : systeme de journalisation
4. %{NKCore.location}/src : fonctionalite fondamentale du moteur
5. %{NKPlatform.location}/src : abstraction de la plateforme
6. %{NKMath.location}/src : mathematique utlise par le moeteur
7. %{NKTime.location}/src : gestion du temps
8. %{NKStream.location}/src : gestion du flux de donnée
9. %{NKFileSystem.location}/src : gestion des systeme de fichiers
10. %{NKMemory.location}/src  : pour la gestion de la memoire
11. %{NKContainers.location}/src : conteneir de donnée
12. %{NKThreading.location}/src : pour la gestion des threads
13. %{NKCollision.location}/src : gestion des collisions
14. %{NKMedia.location}/src : gestion des medias

## Groupe 2 - j'ai une idee, mais je veux verifier

1. %{NKPhysics.location}/src : assurer le rendu physique
2.  %{NKAnima.location}/src : pour la gestion de animatiom

## Groupe 3 -  je ne connais pas suffisamment le role
1. %{NKRenderer.location}/src : Rendu 3D ~80 % d'un MVP UE5-like (PBR, IBL HDR + convolutions GPU, CSM/Virtual Shadow Maps, Planar Reflection, Bloom, ACES, Voxel AO) ; 4 backends GPU à parité (Vulkan/OpenGL/DX11/DX12) ; viewport d'édition (gizmos, view modes, edit mode) ; capture PNG + enregistrement vidéo MP4 asynchrone (fenêtre vivante, doc)
2. %{wks.location}/Externals : 
3. %{NKGlad.location}/include :
4. %{NKRHI.location}/src : RHI bas niveau 6 backends — validé bout-en-bout sur 5 (Vulkan · OpenGL · DX11 · DX12 · Software) ; compute & cross-compile de shaders
5. %{NKSL.location}/src :
6. %{NKSerialization.location}/src : JSON / XML / YAML / binaire / NkNative
7. %{NKReflection.location}/src : reflexion minimal 