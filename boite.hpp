#ifndef BOITE_H
#define BOITE_H

#include <iostream>
#include <list>

using namespace std;

class Particule
{
    public:
    double r_x , r_y, r_z;
    double v_x , v_y , v_z;
    double F_x , F_y , F_z;

    Particule generateur();
};














#endif
