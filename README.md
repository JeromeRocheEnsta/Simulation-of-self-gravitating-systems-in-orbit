# Simulation-of-self-gravitating-systems-in-orbit

La partie décommentée du main permet de modifier les valeurs de:
- t pas de temps 
- M masse du système de plummer
- E énergie du système de plummer
- R rayon de l'orbite du système de plummer
- b_ext et M_ext des paramètres du corps générant la rotation du système de plummer
- mu le coefficient mutiplicateur de la vitesse circulaire intiiale du système de Plummer
- circ booléen qui détermine si on met le système de Plummer en rotation ou non.

Ensuite, suivez les commentaires de la partie décommentée du main.cpp. Les parties commentées nous ont servi à vérifier notre code.

Pour éxécuter le code il faut appliquer la commande:

g++ -std=c++11  src/main.cpp src/particule.cpp src/boite.cpp src/point3d.cpp src/graph_update.cpp src/plummer.cpp src/forces.cpp
puis:
./a.out

En sortie on obtient un fichier resultats.txt

Pour visualiser la modélisation il faut ouvrir le fichier src/traitements.m grâce à matlab et suivre le commentaires du code.
