
#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>

//Constructeur de la boite 
Boite first_box(const list<Particule> & particules){
    Boite B;
    B.level=1;
    list<Particule>::const_iterator it =particules.begin();
    double max_length=0;
    double max_depth =0;
    double max_width =0;
    for (;it!= particules.end(); it++){
            if(max_width < abs(it->r_x)){
                max_width = abs(it->r_x);
            }
            if(max_length < abs(it->r_y)){
                max_length = abs(it->r_y);
            }
            if(max_depth < abs(it->r_z)){
                max_width = abs(it->r_z);
            }
    }
    B.l = 2*max_length;
    B.w = 2*max_width;
    B.d= 2*max_depth;
    B.calculate_mass(particules);
    B.calculate_center_of_mass(particules);
    B.P = NULL;
    return B;

};
