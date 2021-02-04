#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>

// CLass Boite
list<Point2d>& Boite::find_new_centers(){
    list<Point2d> rep;
    Point2d P(C.x - w/4, C.y + l/4),Q(C.x - w/4, C.y - l/4),R(C.x + w/4, C.y + l/4),S(C.x + w/4, C.y + l/4);
    rep.push_back(P);
    rep.push_back(Q);
    rep.push_back(R);
    rep.push_back(S);
    return rep;
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