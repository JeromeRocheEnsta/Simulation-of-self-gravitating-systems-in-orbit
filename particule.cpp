#include "boite.hpp"
#include "math.h"

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


void force(Particule p, Boite *b, double M)  // M est la masse nd'une particule
{   const double G= 6.6742*pow(10,-11);
    const double epsilon = min(b->l,min(b->w,b->d))/100;
    Particule *P_term;
    Point3d Centre=b->G;
    double d,r;
    d=pow(p.r_x-Centre.x,2)+pow(p.r_y-Centre.y,2)+pow(p.r_z-Centre.z,2); //calcul du carre de la distance entre la particule et le centre de la boite

 //Si cette distance est beaucoup plus grande que la distance entre les particules de la boite (sa taille), on fait comme si la boite etait une grande particule,
 // et on passe à la boite soeur

    if (b->l/pow(d,1/2)<epsilon){
        p.F_x=p.F_x-G*b->m*M*(Centre.x-p.r_x)/pow(d,3);
        p.F_y=p.F_y-G*b->m*M*(Centre.y-p.r_y)/pow(d,3);
        p.F_x=p.F_z-G*b->m*M*(Centre.z-p.r_z)/pow(d,3);
        if (b->sister!=0){force(p,b->sister,M);};
        };

   // Si on est face à une boite terminale, et s'il y a une particule dedans, on calcule la force qu'elle exerce sur notre particule,
   // puis on passe a la soeur (qu'il y ai une particule ou non)

   if (b->child==0){
        if (b->P!=0){
            P_term=b->P;
            r=pow(p.r_x-P_term->r_x,2)+pow(p.r_y-P_term->r_y,2)+pow(p.r_z-P_term->r_z,2); //calcul du carre de la distance entre la particule en argument et la particule terminale de la boite
            if (r<=epsilon){r=epsilon;};
            p.F_x=p.F_x-G*b->m*M*(P_term->r_x-p.r_x)/pow(r,3);
            p.F_y=p.F_y-G*b->m*M*(P_term->r_y-p.r_y)/pow(r,3);
            p.F_x=p.F_z-G*b->m*M*(P_term->r_z-p.r_z)/pow(r,3);
        if (b->sister==0){force(p,b->sister,M);};
    };

    // Sinon on passe a la boite fille
    if (b->child!=0){force(p,b->child,M);};

};
}


void Particule::initialisation(double M){
    double t=pow(10,-2);
    v_x=r_x+t*F_x/2*M;
    v_y=r_y+t*F_y/2*M;
    v_z=r_z+t*F_z/2*M;
}

void Particule::mise_a_jour(double M){
    double t=pow(10,-2);
    v_x=r_x+t*F_x/M;
    v_y=r_y+t*F_y/M;
    v_z=r_z+t*F_z/M;
    r_x=r_x+t*v_x;
    r_y=r_y+t*v_y;
    r_z=r_z+t*v_z;
}



ostream & operator<< (ostream & os, const Particule& p)
{   os<<"position:("<<p.r_x<<","<<p.r_y<<","<<p.r_z<<")\n vitesse:("<<p.v_x<<","<<p.v_y<<","<<p.v_z<<") \n Force:("<<p.F_x<<","<<p.F_y<<","<<p.F_z<<")";
    return os;}
