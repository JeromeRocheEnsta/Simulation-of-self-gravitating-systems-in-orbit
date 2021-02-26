#include "boite.hpp"
#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <fstream>
#include <math.h>
 
using namespace std;


int main(int argc, char const *argv[])
{
    /*
    Particule P1(1,0, 0, 0, 0);
    Particule P2(10000,80000, 0, 0, 0,0);
    Particule P3(1,80001,0,0,0,0,0);
    list<Particule> particules;
    particules.push_back(P1);
    particules.push_back(P2);
    particules.push_back(P3);
    Boite primal;
    primal = first_box(particules);
    create_graph(&primal, particules);
    print_graph(&primal);
    all_forces(&primal, &primal);
    cout<<particules.end()->F_x<<endl;
    */

   
    ofstream fichier("resultats.txt", ios::out| ios::trunc);
    if (fichier){
        Particule P1(100000000000,0, 0, 0, 0);
        Particule P2(100,10, 0, 0, 0);
        //Particule P3(1,100/2,sqrt(3)*100*(1/2),0);
        Particule P3(100, -10, 0, 0, 0);
        //cout<<P1<<"\n"<<P2<<endl;
        list<Particule> particules;
        particules.push_back(P1);
        particules.push_back(P2);
        particules.push_back(P3);
        Boite primal;
        primal = first_box(particules);
        create_graph(&primal, particules);
        //print_graph(&primal);
        all_forces(&primal, &primal);
        //On fait évoluer le système sur 10 pas de temps
        int temps=300000;
        int step=0; 
        list<Particule>::iterator it =particules.begin();
        for(;it!=particules.end();it ++){
            fichier<< it->r_x <<"\t"<< it->r_y << "\t"<< it->r_z<<"\t"<<it->v_x<<"\t"<<it->v_y<<"\t"<<it->v_z<<"\t"<<it->F_x<<"\n"<<endl;
            
        }
        global_initialisation(particules);
        for(step=0;step<=temps;step++){
            all_forces(&primal, &primal);
            global_update(particules);
            //affichage_by_step( particules,step);
            //Ecriture dans le fichier
            list<Particule>::iterator it =particules.begin();
            for(;it!=particules.end();it ++){
                fichier<< it->r_x <<"\t"<< it->r_y << "\t"<< it->r_z<<"\t"<<it->v_x<<"\t"<<it->v_y<<"\t"<<it->v_z<<"\t"<<it->F_x<<"\n"<<endl;
            }
            create_graph(&primal, particules);
        }
        fichier.close();
    }
    else{
       cerr << "Cannot open the file" << endl;
    } 
 
    
    //cout<<Test<<endl;
    
    

   return 0;
}
