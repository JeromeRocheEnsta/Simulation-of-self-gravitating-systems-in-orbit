#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>

//Fonction mère
void create_graph(Boite& current,const list<Particule> & particules){
    //On profite de commencer par trouver m et G
    /*
    current.calculate_mass(particules);
    current.calculate_center_of_mass(particules);
    */
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
        Point2d C = current.C;
        Point2d P(C.x - w/4, C.y + l/4),Q(C.x + w/4, C.y + l/4),R(C.x + w/4, C.y - l/4),S(C.x - w/4, C.y - l/4);
        Boite first(current.level, P, current.l/2, current.w/2 );
        Boite second(current.level, Q, current.l/2, current.w/2 );
        Boite third(current.level, R, current.l/2, current.w/2 );
        Boite fourth(current.level, S, current.l/2, current.w/2 );
        first.sister = &second;
        second.sister = &third;
        third.sister = &fourth;
        fourth.sister = NULL;
        current.child = &first;
        //Appliquer la fonction à la soeur et à la première fille
        create_graph( *current.sister, particules);
        create_graph( *current.sister, particules);
    }
}


// CLass Boite
list<Point2d> Boite::find_new_centers(){
    list<Point2d> rep;
    Point2d P(C.x - w/4, C.y + l/4),Q(C.x + w/4, C.y + l/4),R(C.x + w/4, C.y - l/4),S(C.x - w/4, C.y - l/4);
    rep.push_back(P);
    rep.push_back(Q);
    rep.push_back(R);
    rep.push_back(S);
    return rep;
}

int Boite::check_number(const list<Particule> & particules){
    int compteur=0;
    list<Particule>::const_iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) ){
            compteur++;
        }
    }
    return compteur;
}

void Boite::find_unique_child(const list<Particule> & particules){
    list<Particule>::const_iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) ){
            *P= *it;
        }
    }
}



// Class Point2d

Point2d operator + (const Point2d& u, const Point2d& v){
    Point2d w(v);
    return w+=u;
}


Point2d operator - (const Point2d& u, const Point2d& v){
    Point2d w(u);
    return w-=v;
}


Point2d operator * (const Point2d& u,double a){
    Point2d w(u);
    return w*=a;
}
Point2d operator * (double a, const Point2d& u){
    Point2d w(u);
    return w*=a;
}


Point2d operator / (const Point2d& u,double a){
    Point2d w(u);
    return w/=a;
}
Point2d operator / (double a, const Point2d& u){
    Point2d w(u);
    return w/=a;
}

bool operator ==(const Point2d & u, const Point2d &v){
    return (u.x==v.x) && (u.y==v.y);
}

bool operator !=(const Point2d & u, const Point2d &v){
    return !(u==v);
}

ostream & operator <<(ostream & os ,const Point2d& u){
    os<<"( "<<u.x<<", "<<u.y<<" )";
    return os ;
}