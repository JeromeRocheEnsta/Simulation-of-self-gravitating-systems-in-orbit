#include "boite.hpp"
#include "math.h"
#include <list>


////////////////////////////////////////////////
////Calcul de la valeur force sur 1 particule///
////////////////////////////////////////////////



void force(Particule & pr, Boite *b){
    /*
        On va parcourir le graph pour calculer la force totale s'applquant à la particule pr. 
        Cette fonction est récursive et son premier appel doit être avec la boite primal du graph
        entrée: Référence sur la particule considéré + Boite que l'on parcours actuellement dans le graphe
        sortie: rien on met à jour la force boîte après boîte.
    */
    //const double G= 6.6742E-11;
    const double G= 1;
    const double epsilon1 = max(b->l,max(b->w,b->d)); //distance négligeable devant 
    const double epsilon2 = 1E-2; //facteur d'adoucissement
    Particule *P_term;
    Point3d Centre=b->G;
    double d,r;
    d=pow(pr.r_x-Centre.x,2)+pow(pr.r_y-Centre.y,2)+pow(pr.r_z-Centre.z,2);

    /*Calcul de la distance entre le centre G de la boite et la particule que l'on traite
    Si cette distance/100 est plus grande que epsilon1 on est dans le cas où la distance entre les particules compris dans la boite b 
    est très petite devant la distance à notre particule*/
    if (epsilon1 < sqrt(d)/10 ){
        //facteur d'adoucissement
        if (d<=epsilon2){d=epsilon2;}
        pr.F_x += G * b->m * pr.m * (Centre.x - pr.r_x) / sqrt(pow(d,3));
        pr.F_y += G * b->m * pr.m * (Centre.y - pr.r_y) / sqrt(pow(d,3));
        pr.F_z += G * b->m * pr.m * (Centre.z - pr.r_z) / sqrt(pow(d,3));
        //Pas de boucle car on ne s'intéresse pas aux enfants
    }
    else{
        if (b->child==0){
            if (b->P != 0 && b->P != &pr){
                P_term = b->P;
                r = pow(pr.r_x-P_term->r_x,2) + pow(pr.r_y-P_term->r_y,2) + pow(pr.r_z-P_term->r_z,2); //calcul du carre de la distance entre la particule en argument et la particule terminale de la boite
                //facteur d'adoucissement
                if (r<=epsilon2){r=epsilon2;}
                pr.F_x += G * P_term->m * pr.m * (P_term->r_x - pr.r_x) / sqrt(pow(r,3));
                pr.F_y += G * P_term->m * pr.m * (P_term->r_y - pr.r_y) / sqrt(pow(r,3));
                pr.F_z += G * P_term->m * pr.m * (P_term->r_z - pr.r_z) / sqrt(pow(r,3));
            }
        }
        //Boucle de récursion
        else{
            force(pr,b->child);
        }
    }


    //Boucle de récursion
    if (b->sister!=0){
        force(pr,b->sister);
    }
}


/////////////////////////////////////////////////
////Calcul de la valeur de chaque force/////////
////////////////////////////////////////////////

/*
On peut faire beaucoup mieux en changeant current par particules ainsi on parcours seulement la liste des particules plutôt que le graph....
*/
void all_forces(Boite * primal, Boite * current, bool circ, double M_ext, double b_ext){
    /*
    Parcours du graphe afin de traiter toutes les particules
    Entrée: 
        primal: c'est la boite de niveau 1, on en aura besoin dans le calcul de force afin de parcourir le graph
        current: Boite que l'on traite actuellement.
    Sortie:
        Après avoir appliqué cette fonction, on aura calculé toutes les forces gravitationnelle s'appliquant sur toutes nos particules.
        Etape nécessaire pour faire évoluer notre système
    */
   //Si c'est une boite terminale avec une seule particule on calcule la force 
   if (current->P != NULL){
       //Remise à zéro des forces !
       current->P->F_x = 0;
       current->P->F_y = 0;
       current->P->F_z = 0;
       force(*current->P, primal);
       if(circ == true){
            double r = pow(current->P->r_x, 2) + pow(current->P->r_y, 2) + pow(current->P->r_z, 2);
            
            r += b_ext*b_ext;
            
            r = pow(r, 3./2);
            r = 1/r;
            r *= - current->P->m * M_ext;
            current->P->F_x = r* current->P->r_x;
            current->P->F_y = r* current->P->r_y;
            current->P->F_z = r* current->P->r_z;
       }
   }

   //Sinon on vérifie si elle a un enfant et on fait le calcul
   if(current->child != NULL){
       all_forces(primal ,current->child, circ, M_ext, b_ext);
   }

   // En meme temps on regarde pour ces soeurs 
   if(current->sister != NULL){
       all_forces(primal, current->sister, circ, M_ext, b_ext);
   }
}