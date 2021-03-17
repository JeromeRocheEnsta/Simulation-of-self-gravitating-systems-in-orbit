#include "boite.hpp"
#include "math.h"
#include <list>


#define PI 3.141592 



list<Particule> generateur_plummer(double N, double M, double E, double R, double mu, bool circ, double M_ext, double b_ext)
{
    /*
    Génération de conditions initiales
    */
    list<Particule> particules;
    double x,x_1,x_2,x_3,x_4,v,v_e,r;
    x = 1.0/RAND_MAX;

    for(int i=0; i<N; i++){
        Particule P;
        double u_r=2;
        double u_v=2;

        //Calcul du rayon
        x_1 = x*rand();
        r=pow(x_1,-2./3);
        r=0.999*r-1;
        r=sqrt(r);
        r=1/r;
        
        while (u_r>1){
            x_2 = 2*(x*rand()-0.5);
            x_3 = 2*(x*rand()-0.5);
            x_4 = 2*(x*rand()-0.5);
            u_r=pow(pow(x_2,2)+pow(x_3,2)+pow(x_4,2),1./2);
        }
        //Calcul des coordonnées
        P.r_x=r*x_2/u_r;
        P.r_y=r*x_3/u_r;
        P.r_z=r*x_4/u_r;


        //Calcul de la vitesse d'échappement ve
        v_e=sqrt(2)*pow((1+pow(r,2)), -1./4);

        //Calcul de la vitesse v
        x_1 = x*rand();
        x_2 = x*rand();
        while (x_2 >= 10*pow(x_1,2)*pow(1-pow(x_1,2),7./2)){
            x_1 = x*rand();
            x_2 = x*rand();
        }
        v=x_1*v_e;

        while (u_v>1){
            x_2 = 2*(x*rand()-0.5);
            x_3 = 2*(x*rand()-0.5);
            x_4 = 2*(x*rand()-0.5);
            
            u_v=sqrt(pow(x_2,2)+pow(x_3,2)+pow(x_4,2));
        }
        
        P.v_x=v*x_2/u_v;
        P.v_y=v*x_3/u_v;
        P.v_z=v*x_4/u_v;

        //Finitions
        P.F_x=0;
        P.F_y=0;
        P.F_z=0;
        P.m = (double)1/N;

        
        //Ajout à la liste de particules
        particules.push_back(P);
    }

    //Normalisation à la masse M et l'Energie E
    list<Particule>::iterator it =particules.begin();
    for(;it!=particules.end();it ++){
        it->m *= M;
        
        it->r_x *= 3*PI*M*M/(64*(-E));
        it->r_y *= 3*PI*M*M/(64*(-E));
        it->r_z *= 3*PI*M*M/(64*(-E));
        it->v_x *= 64*sqrt(-E)/(4*PI*sqrt(M));
        it->v_y *= 64*sqrt(-E)/(4*PI*sqrt(M));
        it->v_z *= 64*sqrt(-E)/(4*PI*sqrt(M));
    }
    
    if(circ == true){
        Plummer_circ(particules, R, M_ext, mu, b_ext);
    }

    return particules;
}


void Plummer_circ(list<Particule>& particules, double R, double M_ext, double mu, double b_ext){
    /*
    Si on veut mettre en orbite notre système de Plummer, il faut ajouter une vitesse selon e_theta et décentrer le système
    */
    list<Particule>::iterator it =particules.begin();
    double v_circ = R*R;
    v_circ += b_ext*b_ext;
    v_circ = pow(v_circ, 3./4);
    v_circ = 1/ v_circ;
    v_circ *= R*sqrt(M_ext);
    for(;it!=particules.end();it ++){
        it->r_x += R;
        it->v_y += mu * v_circ;
    }
}