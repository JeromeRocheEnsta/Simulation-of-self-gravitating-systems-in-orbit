#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

//Fonction mère
void create_graph(Boite* current,const list<Particule> & particules){
    cout<<current<<endl;
    cout<<current->check_number(particules)<<endl;
    //On profite de commencer par trouver m et G
    current->calculate_mass(particules);
    
    current->calculate_center_of_mass(particules);
    
    //Corps de la fonction
    if(current->check_number(particules)==0){
        current->P = NULL;
        cout<<"COucou"<<endl;
    }
    else if(current->check_number(particules)==1){
        cout<<"Encule"<<endl;
        //SEGMENTATION FAULT ICI
        current->find_unique_child(particules);
    }else{
        cout<<"Je suis al"<<endl;
        //Créer les enfants
        double w = current->w;
        double l = current->l;
        double d = current->d;
        Point3d C = current->C;
        Point3d P(C.x - w/4, C.y + l/4,C.z + d/4),Q(C.x + w/4, C.y + l/4, C.z + d/4),R(C.x + w/4, C.y - l/4, C.z + d/4),S(C.x - w/4, C.y - l/4, C.z + d/4),T(C.x - w/4, C.y + l/4,C.z + d/4),U(C.x + w/4, C.y + l/4, C.z + d/4),V(C.x + w/4, C.y - l/4, C.z + d/4),W(C.x - w/4, C.y - l/4, C.z + d/4);
        current->child = new Boite(current->level + 1, P, l/2, w/2, d/2 );
        current->child->sister = new Boite(current->level + 1, Q, l/2, w/2, d/2 );
        current->child->sister->sister = new Boite(current->level + 1, R, l/2, w/2, d/2 );
        current->child->sister->sister->sister = new Boite(current->level + 1, S, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister = new Boite(current->level + 1, T, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister->sister = new Boite(current->level + 1, U, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister->sister->sister = new Boite(current->level + 1, V, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister->sister->sister->sister = new Boite(current->level + 1, W, l/2, w/2, d/2 );
        //Appliquer la fonction à la soeur et à la première fille
        cout<<"Cou"<<endl;
        cout<<current->sister<<endl;
        if(current->sister != 0){
            create_graph( current->sister, particules);
        }
        cout<<"1er erreur traitée"<<endl;
        cout<<current->child<<endl;
        create_graph( current->child, particules);
    }
}

//Construction première boite
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
                max_depth = abs(it->r_z);
            }
    }
    Point3d C(0,0,0);
    B.C = C; 
    B.l = 2*max_length + 1;
    B.w = 2*max_width+ 1;
    B.d= 2*max_depth + 1;
    B.calculate_mass(particules);
    B.calculate_center_of_mass(particules);
    B.P = NULL;
    return B;

};


// CLass Boite

int Boite::check_number(const list<Particule> & particules){
    int compteur=0;
    list<Particule>::const_iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            compteur++;
        }
    }
    return compteur;
}

void Boite::find_unique_child(const list<Particule> & particules){
    list<Particule>::const_iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            *P= *it;
        }
    }
}

void Boite::calculate_mass(const list<Particule> & particules){
    m=0;
    list<Particule>::const_iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            m+= it->m;
        }
    }
}

void Boite::calculate_center_of_mass(const list<Particule> & particules){
    G.x=0;
    G.y=0;
    G.z=0;
    list<Particule>::const_iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            G.x += it->m*it->r_x;
            G.y += it->m*it->r_y;
            G.z += it->m*it->r_z;
        }
    }
    G/=m;
}


ostream & operator<< (ostream & os, const Boite& B){
    os<<"Centre:("<<B.C.x<<","<<B.C.y<<","<<B.C.z<<")\n largeur:("<<B.w<<") \n  longueur:("<<B.l<<") \n width:("<<B.d<<") \n";
    return os;
}


// Class Point3d

Point3d operator + (const Point3d& u, const Point3d& v){
    Point3d w(v);
    return w+=u;
}


Point3d operator - (const Point3d& u, const Point3d& v){
    Point3d w(u);
    return w-=v;
}


Point3d operator * (const Point3d& u,double a){
    Point3d w(u);
    return w*=a;
}
Point3d operator * (double a, const Point3d& u){
    Point3d w(u);
    return w*=a;
}


Point3d operator / (const Point3d& u,double a){
    Point3d w(u);
    return w/=a;
}
Point3d operator / (double a, const Point3d& u){
    Point3d w(u);
    return w/=a;
}

bool operator ==(const Point3d & u, const Point3d &v){
    return (u.x==v.x) && (u.y==v.y);
}

bool operator !=(const Point3d & u, const Point3d &v){
    return !(u==v);
}

ostream & operator <<(ostream & os ,const Point3d& u){
    os<<"( "<<u.x<<", "<<u.y<<" )";
    return os ;
}
