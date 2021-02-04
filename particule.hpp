#ifndef PARTICULE_H
#define PARTICULE_H

#include <iostream>
#include <list>

using namespace std;

class Particule
{
    public:
    double r_x , r_y, r_z;
    double v_x , v_y , v_z;
    double F_x , F_y , F_z;

    Particule(double r_x_=0,double r_y_=0, double r_z_=0 ,double v_x_=0,double v_y_=0, double v_z_=0,double F_x_=0,double F_y_=0, double F_z_=0):
        r_x(r_x_),r_y(r_y_),r_z(r_z_),v_x(v_x_),v_y(v_y_),v_z(v_z_),F_x(F_x_),F_y(F_y_),F_z(F_z_){}

    void generateur();

};

ostream & operator <<(ostream &,const Particule&);














#endif