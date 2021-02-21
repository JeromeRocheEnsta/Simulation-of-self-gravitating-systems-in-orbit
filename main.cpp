#include "boite.hpp"
#include <iostream>
#include <list>
#include <cstdlib>


int main(int argc, char const *argv[])
{
    /*
    Particule P1(300,1, 1, 0, 0,1,2);
    Particule P2(3,-1, 1, 0, 1,-2);
    Particule P3(1,4,5,6,2,0,0);
    */
    Particule P1(300,0, 0, 0, 1);
    Particule P2(300,0, 1, 0, -1);
    cout<<P1<<"\n"<<P2<<endl;
    list<Particule> particules;
    particules.push_back(P1);
    particules.push_back(P2);
    //particules.push_back(P3);
    Boite primal;
    primal = first_box(particules);
    create_graph(&primal, particules);
    print_graph(&primal);
    all_forces(&primal, &primal);
    //On fait évoluer le système sur 50 pas de temps
    
    int temps=10;
    int step=0;
    global_initialisation(particules);
    for(step=0;step<=temps;step++){
        all_forces(&primal, &primal);
        cout<<particules.front()<<" "<<particules.back()<<"\n";
        global_update(particules);
        affichage_by_step( particules,step);
        create_graph(&primal, particules);
    }
    


    //cout<<Test<<endl;
    /*
    print_graph(&primal);
    force(P1, &primal);
    force(P2, &primal);
    cout<<P1.F_x<<endl;
    cout<<P2.F_x<<endl;
    */
    return 0;
}
