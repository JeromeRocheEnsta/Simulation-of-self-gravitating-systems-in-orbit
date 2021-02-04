#include "calcul_iteration.h"



void calcul_iterations(std::list<Particule&> & liste_particules, Boite& boite)
{
    //Fonction qui calcule les itérations de calcul du paragraphe 3.1
    //On prend la liste des particules et la boite mère


    //Calcul des forces gravitationnelles pour chaque particule
        //On boucle sur les particules
        for(int i=0;i<liste_particules.size();i++)
        {
            //fonction qui calcule la force exercée sur la particule i
            liste_particules[i].force(&boite);
        }
    //Mise à jour des vitesses et des positions
        for(int i=0;i<liste_particules.size();i++)
        {
            //Maj de la vitesse et position de la boite i
            liste_particules[i].mise_a_jour();
        }
    //Mise à jour des boites

        //On appelle la fction de maj des boites.

        boite.mise_a_jour();

}

