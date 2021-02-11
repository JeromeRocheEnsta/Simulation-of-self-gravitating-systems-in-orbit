#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

//Fonction mère
void create_graph(Boite& current,const list<Particule> & particules){
    //On profite de commencer par trouver m et G
    current.calculate_mass(particules);
    current.calculate_center_of_mass(particules);
    //Corps de la fonction
    if(current.check_number(particules)==0){
        current.P = NULL;
    }
    else if(current.check_number(particules)==1){
        current.find_unique_child(particules);
    }else{
        //Créer les enfants
        double w = current.w;
        double l = current.l;
        double d = current.d;
        Point3d C = current.C;
        Point3d P(C.x - w/4, C.y + l/4,C.z + d/4),Q(C.x + w/4, C.y + l/4, C.z + d/4),R(C.x + w/4, C.y - l/4, C.z + d/4),S(C.x - w/4, C.y - l/4, C.z + d/4),T(C.x - w/4, C.y + l/4,C.z + d/4),U(C.x + w/4, C.y + l/4, C.z + d/4),V(C.x + w/4, C.y - l/4, C.z + d/4),W(C.x - w/4, C.y - l/4, C.z + d/4);
        Boite first(current.level + 1, P, current.l/2, current.w/2, current.d/2 );
        Boite second(current.level + 1, Q, current.l/2, current.w/2, current.d/2 );
        Boite third(current.level + 1, R, current.l/2, current.w/2, current.d/2);
        Boite fourth(current.level + 1, S, current.l/2, current.w/2, current.d/2 );
        Boite fifth(current.level + 1, T, current.l/2, current.w/2, current.d/2 );
        Boite sixth(current.level + 1, U, current.l/2, current.w/2, current.d/2 );
        Boite seventh(current.level + 1, V, current.l/2, current.w/2, current.d/2 );
        Boite eighth(current.level + 1, W, current.l/2, current.w/2, current.d/2 );

        first.sister = &second;
        second.sister = &third;
        third.sister = &fourth;
        fourth.sister = &fifth;
        fifth.sister = &sixth;
        sixth.sister = &seventh;
        seventh.sister = &eighth;
        eighth.sister = NULL;
        current.child = &first;
        //Appliquer la fonction à la soeur et à la première fille
        create_graph( *current.sister, particules);
        create_graph( *current.sister, particules);
    }
}


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
    double m=0;
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
    os<<"Centre:("<<B.C.x<<","<<B.C.y<<","<<B.C.z<<")\n longueur:("<<B.l<<") \n largeur:("<<B.w<<") \n width:("<<B.l<<") \n";
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
