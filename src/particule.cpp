#include "boite.hpp"
#include "math.h"
#include <list>


#define PI 3.141592 

//////////////////////////////////////////
///////Vitesse initiale des particules////
//////////////////////////////////////////

void Particule::initialisation(double t){
    /*
    Inisitalisation du schéma saute-mouton (v^{1/2})
    */
    v_x=v_x+t*F_x/(2*m);
    v_y=v_y+t*F_y/(2*m);
    v_z=v_z+t*F_z/(2*m);
}

void global_initialisation(list<Particule> & particules, double t){
    /*
        entrée: liste de particules qu'on initialisera leur vitesse initiale
        sortie: rien on modifie les vitesses 
    */
    list<Particule>::iterator  it=particules.begin();
     for(;it!= particules.end();it++){
         it->initialisation(t);
     }
}


//////////////////////////////
///////Schéma saute-mouton////
//////////////////////////////

void Particule::mise_a_jour(double t){
    v_x=v_x+t*F_x/m;
    v_y=v_y+t*F_y/m;
    v_z=v_z+t*F_z/m;
    r_x=r_x+t*v_x;
    r_y=r_y+t*v_y;
    r_z=r_z+t*v_z;
}


void global_update(list<Particule> & particules, double t){
    /*
        entrée: liste de particules 
        sortie: rien on met à jour leur position 
    */

    list<Particule>::iterator  it=particules.begin();
    for(; it!=particules.end(); it++){
        it->mise_a_jour(t);
    }
}






//Surchareg de l'opérateur flux pour afficher une particule
ostream & operator<< (ostream & os, Particule& p)
{   os<<"masse:"<<p.m<<"\nposition:("<<p.r_x<<","<<p.r_y<<","<<p.r_z<<")\n vitesse:("<<p.v_x<<","<<p.v_y<<","<<p.v_z<<") \n Force:("<<p.F_x<<","<<p.F_y<<","<<p.F_z<<")";
    return os;}



