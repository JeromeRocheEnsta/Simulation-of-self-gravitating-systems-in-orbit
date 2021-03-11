#include "boite.hpp"
#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
#include <fstream>
#include <math.h>
 
using namespace std;


int main(int argc, char const *argv[]){
    
    /*
    //Tests fonctions force
    Particule P1(1,0, 0, 0, 0);
    Particule P2(1000000000000,80000, 0, 0, 0,0);
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
    list<Particule>::iterator it =particules.begin();
    for(;it!=particules.end();it ++){
        cout<<*it<<endl;
    }
    int iter=40;
    global_initialisation(particules);
    cout<<"\n"<<endl;
    for(int i=0; i<iter; i++){
        all_forces(&primal, &primal);
        global_update(particules);
        create_graph(&primal, particules);
        list<Particule>::iterator it =particules.begin();
        for(;it!=particules.end();it ++){
            cout<<*it<<endl;
        }
        cout<<"\n"<<endl;
    }
    */

   /*
   //Tests génération modèle de Plummer
    list<Particule> particules;
    particules = generateur_plummer(5);
    list<Particule>::iterator it =particules.begin();
    for(;it!=particules.end();it ++){
        cout<<*it<<endl;
    }
    */
   
    
    double parsec =1E16; // Reférence pour la longueur
    double m_ref =1E36; // Référence pour la masse 
    double ref_temps = 1E4; //Référence unité de temps 
    double ref_vit = parsec/ref_temps ;

    /*
    ofstream fichier("resultats.txt", ios::out| ios::trunc);
    if (fichier){
        Particule P1(1E-6,0, 0, 0, 0);
        Particule P2(1E-12,1E-9, 0, 0, 0,1E7/ref_vit);
        //Particule P3(1./3,90,0,0,0,0,0);
        list<Particule> particules;
        particules.push_back(P1);
        particules.push_back(P2);
        //particules.push_back(P3);
        Boite primal;
        primal = first_box(particules);
        create_graph(&primal, particules);
        //print_graph(&primal);
        all_forces(&primal, &primal);
        global_initialisation(particules);
        //On fait évoluer le système sur 10 pas de temps
        int temps=3000000;
        int step=0; 
        list<Particule>::iterator it =particules.begin();
        for(;it!=particules.end();it ++){
            fichier<< parsec*it->r_x <<"\t"<< parsec*it->r_y << "\t"<< parsec*it->r_z<<"\t"<<it->v_x<<"\t"<<it->v_y<<"\t"<<it->v_z<<'\t'<<it->F_x<<'\t'<<it->F_y<<"\n"<<endl;
        }
        
        for(step=0;step<=temps;step++){
            all_forces(&primal, &primal);
            global_update(particules);
            //affichage_by_step( particules,step);
            //Ecriture dans le fichier
            list<Particule>::iterator it =particules.begin();
            for(;it!=particules.end();it ++){
                fichier<< parsec*it->r_x <<"\t"<< parsec*it->r_y << "\t"<< parsec*it->r_z<<"\t"<<ref_vit*it->v_x<<"\t"<<ref_vit*it->v_y<<"\t"<<ref_vit*it->v_z<<'\t'<<it->F_x<<'\t'<<it->F_y<<"\n"<<endl;
            }
            create_graph(&primal, particules);
        }
        fichier.close();
    }
    else{
       cerr << "Cannot open the file" << endl;
    } 
    */



    //Test des nouvelles fonctionnalités update_graph

    
    //cout<<Test<<endl;
    Particule P1(1,0.5, 0, 0, 0);
    Particule P2(10,-1, 0, 0, 0,0);
    Particule P3(10,1, 0, 0, 0,0);
    list<Particule> particules;
    particules.push_back(P1);
    particules.push_back(P2);
    particules.push_back(P3);
    
    Boite primal;
    primal = first_box(particules);
    create_graph(&primal, particules);
    print_graph(&primal);
    particules.front().r_x = -0.5;
    list<Particule>::iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        cout<<*it<<endl;
    }
    eliminate_and_add_graph(primal, primal, particules);
    print_graph(&primal);
    //is_particules_out(primal, particules);
    //eliminate_and_add_graph(primal, particules);
    //print_graph(&primal);
    //cout<<"Entre deux"<<endl;
    //print_graph(&primal);
    



    return 0;
}
