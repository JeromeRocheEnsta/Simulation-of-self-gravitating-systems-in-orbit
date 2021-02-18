#include "boite.hpp"
#include <iostream>
#include <list>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    Particule P1(1, 1, 0, 2);
    Particule P2(0.5, 0.5, 0, 1);
    cout<<P1<<"\n"<<P2<<endl;
    list<Particule> particules;
    particules.push_back(P1);
    particules.push_back(P2);
    Boite Test;
    Test = first_box(particules);
    cout<<Test<<endl;
    create_graph(&Test, particules);
    print_graph(&Test);
    return 0;
}
