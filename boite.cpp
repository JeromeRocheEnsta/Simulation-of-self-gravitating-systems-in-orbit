#include "boite.hpp"
#include<stdlib.h>
#include<math.h>

Particule Particule::generateur()
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
    v=x_1;
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
