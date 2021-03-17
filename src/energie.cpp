#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

using namespace std;

///////////////////////////////////////////////////////////
///On calcule l'énergie potentielle de chaque particules///
///////////////////////////////////////////////////////////

void energie_potentielle(Particule & pr, Boite *b){
    /*
        On va parcourir le graph pour calculer l'énergie potentielle totale s'appliquant à la particule pr. 
        Cette fonction est récursive et son premier appel doit être avec la boite primal du graph
        entrée: Référence sur la particule considéré + Boite que l'on parcours actuellement dans le graphe
        sortie: rien on met à jour la force boîte après boîte.
    */
    const double G= 1;
    const double epsilon1 = max(b->l,max(b->w,b->d)); //distance négligeable devant 
    const double epsilon2 = 1E-6; //facteur d'adoucissement
    Particule *P_term;
    Point3d Centre=b->G;
    double d,r;
    d=sqrt(pow(pr.r_x-Centre.x,2)+pow(pr.r_y-Centre.y,2)+pow(pr.r_z-Centre.z,2));

    /*Calcul de la distance entre le centre G de la boite et la particule que l'on traite
    Si cette distance/100 est plus grande que epsilon1 on est dans le cas où la distance entre les particules compris dans la boite b 
    est très petite devant la distance à notre particule*/
    if (epsilon1 < d/100 ){
        //facteur d'adoucissement
        //cout<<"epsilon1\n"<<endl;
        if (d<=epsilon2){d=epsilon2;}
        if(b->m!=0){pr.E_p -= G*(b->m*pr.m)/d;}
        //cout <<"E_p_ext="<<pr.E_p<<"\n" <<endl;
        //Pas de boucle car on ne s'intéresse pas aux enfants
    }
    else{
        if (b->child==0){
            if (b->P != 0 && b->P != &pr){
                P_term = b->P;
                r = sqrt(pow(pr.r_x-P_term->r_x,2) + pow(pr.r_y-P_term->r_y,2) + pow(pr.r_z-P_term->r_z,2)); //calcul du carre de la distance entre la particule en argument et la particule terminale de la boite
                //facteur d'adoucissement
                if (r<=epsilon2){r=epsilon2;}
                if(b->m!=0) {pr.E_p -=  G*b->m*pr.m/r;}
                //cout <<"E_p_ext="<<pr.E_p<<"\n" <<endl;
            }
        }
        //Boucle de récursion
        else{
            energie_potentielle(pr,b->child);
        }
    }


    //Boucle de récursion
    if (b->sister!=0){
        energie_potentielle(pr,b->sister);
    }
    

}

void all_potential_energy(Boite * primal, Boite * current){
    /*Parours le graphe et calcul l'énergie potentielle de chaque particule 
    Entrée: 
        primal: c'est la boite de niveau 1, on en aura besoin dans le calcul de force afin de parcourir le graph
        current: Boite que l'on traite actuellement.
    Sortie:
        Après avoir appliqué cette fonction, on aura calculé toutes les forces gravitationnelle s'appliquant sur toutes nos particules.
        Etape nécessaire pour faire évoluer notre système
    */
   //Si c'est une boite terminale avec une seule particule on calcule la force
    if (current->P != NULL)
    {
        //Remise à zéro de l'énergie !
        current->P->E_p = 0;
        energie_potentielle(*current->P, primal);
    }

    //Sinon on vérifie si elle a un enfant et on fait le calcul
    if (current->child != NULL)
    {
        all_potential_energy(primal, current->child);
    }

    // En meme temps on regarde pour ces soeurs
    if (current->sister != NULL)
    {
        all_potential_energy(primal, current->sister);
    }
}


//////////////////////////////////////////////////
////Calcul de l'énergie mécanique du système/////
/////////////////////////////////////////////////

double mecanic_energy_system(list<Particule>& particules){
    double E_m_system=0;
    list<Particule>::iterator it = particules.begin();
    for(;it != particules.end(); it++){
        E_m_system += it->E_c + it->E_p;
    }
    return E_m_system;
}