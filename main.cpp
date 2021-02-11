#include "boite.hpp"
#include <iostream>
#include <list>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    Particule P1(5, 1, 10);
    Particule P2(-5, 1, 10);
    cout<<P1<<"\n"<<P2<<endl;
    list<Particule> particules;
    particules.push_back(P1);
    particules.push_back(P2);
    Boite Test;
    Test = first_box(particules);
    cout<<Test<<endl;
    create_graph(&Test, particules);


    return 0;
}
