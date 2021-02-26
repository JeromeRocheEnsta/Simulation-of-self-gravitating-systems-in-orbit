#include "boite.hpp"
#include "math.h"
#include <list>


void Particule::generateur()
{
    double x,x_1,x_2,x_3,x_4,v,v_e,r;
    x = 1.0/RAND_MAX;
    double u_r=2;
    double u_v=2;
    while (u_r>1){
        x_1 = x*rand();
        x_2 = x*rand();
        x_3 = x*rand();
        x_4 = x*rand();
        r=pow(0.999*pow(x_1,-2/3)-1,-1/2);
        u_r=pow(pow(x_2,2)+pow(x_3,2)+pow(x_4,2),1/2);
    }
    r_x=r*x_2/u_r;
    r_y=r*x_3/u_r;
    r_z=r*x_4/u_r;

    x_1 = x*rand();
    x_2 = x*rand();
    v_e=sqrt(2)*(1+pow(r,2))*(-1/4);
    while (x_2<10*pow(x_1,2)*pow(1-pow(x_1,2),7/2)){
        x_1 = x*rand();
        x_2 = x*rand();
    }
    v=x_1*v_e;
    while (u_v>1){
        x_1 = x*rand();
        x_2 = x*rand();
        x_3 = x*rand();
        x_4 = x*rand();
        u_v=pow((pow(x_2,2)+pow(x_3,2)+pow(x_4,2)),1/2);
    }
    v_x=v*x_2/u_v;
    v_y=v*x_3/u_v;
    v_z=v*x_4/u_v;
}


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
    const double G= 6.6742E-11;
    const double epsilon1 = max(b->l,max(b->w,b->d)); //distance négligeable devant 
    const double epsilon2 = 1E-2; //facteur d'adoucissement
    Particule *P_term;
    Point3d Centre=b->G;
    double d,r;
    d=pow(pr.r_x-Centre.x,2)+pow(pr.r_y-Centre.y,2)+pow(pr.r_z-Centre.z,2);

    /*Calcul de la distance entre le centre G de la boite et la particule que l'on traite
    Si cette distance/100 est plus grande que epsilon1 on est dans le cas où la distance entre les particules compris dans la boite b 
    est très petite devant la distance à notre particule*/
    if (epsilon1 < pow(d, 1/2)/10 ){

        //facteur d'adoucissement
        if (d<=epsilon2){d=epsilon2;}
        pr.F_x += G * b->m * pr.m * (Centre.x - pr.r_x) / pow(d,3/2);
        pr.F_y += G * b->m * pr.m * (Centre.y - pr.r_y) / pow(d,3/2);
        pr.F_z += G * b->m * pr.m * (Centre.z - pr.r_z) / pow(d,3/2);
        //Boucle de récursion
        if(b->child != 0){
            force(pr,b->child);
        }
    }
    else{
        if (b->child==0){
            if (b->P != 0 && b->P != &pr){
                //cout<<"on calcule"<<endl;
                P_term = b->P;
                r = pow(pr.r_x-P_term->r_x,2) + pow(pr.r_y-P_term->r_y,2) + pow(pr.r_z-P_term->r_z,2); //calcul du carre de la distance entre la particule en argument et la particule terminale de la boite
                //facteur d'adoucissement
                if (r<=epsilon2){r=epsilon2;}
                pr.F_x += G * b->m * pr.m * (P_term->r_x - pr.r_x) / pow(r,3/2);
                pr.F_y += G * b->m * pr.m * (P_term->r_y - pr.r_y) / pow(r,3/2);
                pr.F_z += G * b->m * pr.m * (P_term->r_z - pr.r_z) / pow(r,3/2);
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
void all_forces(Boite * primal, Boite * current){
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
       //cout<<"Coucou"<<endl;
       //cout<<*current->P<<endl;
       //Remise à zéro des forces !
       current->P->F_x = 0;
       current->P->F_y = 0;
       current->P->F_z = 0;
       force(*current->P, primal);
   }

   //Sinon on vérifie si elle a un enfant et on fait le calcul
   if(current->child != NULL){
       all_forces(primal ,current->child);
   }

   // En meme temps on regarde pour ces soeurs 
   if(current->sister != NULL){
       all_forces(primal, current->sister);
   }

}



//////////////////////////////////////////
///////Vitesse initiale des particules////
//////////////////////////////////////////

void Particule::initialisation(){
    double t=1E-2;
    v_x=v_x+t*F_x/2*m;
    v_y=v_y+t*F_y/2*m;
    v_z=v_z+t*F_z/2*m; //J'ai changé r_x en v_x etc.. c'était pas homogène 
}

void global_initialisation(list<Particule> & particules){
    /*
        entrée: liste de particules qu'on initialisera leur vitesse initiale
        sortie: rien on modifie les vitesses 
    */
    list<Particule>::iterator  it=particules.begin();
     for(;it!= particules.end();it++){
         it->initialisation();
     }
}


//////////////////////////////
///////Schéma saute-mouton////
//////////////////////////////

void Particule::mise_a_jour(){
    int test=1;
    double t=1E-2;
    switch (test){
        case 0:
            v_x=r_x+t*F_x/m;
            v_y=r_y+t*F_y/m;
            v_z=r_z+t*F_z/m;
            r_x=r_x+t*v_x;
            r_y=r_y+t*v_y;
            r_z=r_z+t*v_z;
        case 1:
            v_x=v_x+t*F_x/m;
            v_y=v_y+t*F_y/m;
            v_z=v_z+t*F_z/m;
            r_x=r_x+t*v_x;
            r_y=r_y+t*v_y;
            r_z=r_z+t*v_z;

    }
}


void global_update(list<Particule> & particules){
    /*
        entrée: liste de particules 
        sortie: rien on met à jour leur position 
    */

    list<Particule>::iterator  it=particules.begin();
    for(; it!=particules.end(); it++){
        it->mise_a_jour();
    }
}


ostream & operator<< (ostream & os, Particule& p)
{   os<<"masse:"<<p.m<<"\nposition:("<<p.r_x<<","<<p.r_y<<","<<p.r_z<<")\n vitesse:("<<p.v_x<<","<<p.v_y<<","<<p.v_z<<") \n Force:("<<p.F_x<<","<<p.F_y<<","<<p.F_z<<")";
    return os;}


//Fonction qui nous permet de montrer l'état du sytème à chaque itérations 
void affichage_by_step(list<Particule> particules, int k ){
   
    //cout<<"--------------------------------------------------------------------------------------\n"<<endl;
    cout<<"Itérations"<<k<<"\n"<<endl; 
    //list<Particule>::iterator it =particules.begin();
    //int i=0;
    //for(;it!=particules.end();it ++){
        //cout<<"Particule "<<i<<": \t x="<< it->r_x <<"\t y="<< it->r_y << "\t z="<< it->r_z<<"\n"<<endl;
        //i += 1;
    //}
}
