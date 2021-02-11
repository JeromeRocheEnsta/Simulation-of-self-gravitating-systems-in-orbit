#include "boite.hpp"
#include <iostream>
#include <list>
#include <cstdlib>

int main(int argc, char const *argv[])
{
    Particule P1(1, 1);
    Particule P2(-1, 1);
    cout<<P1<<"\n"<<P2<<"\n"<<endl;
    list<Particule> particules;
    particules.push_back(P1);
    particules.push_back(P2);


    return 0;
}
