#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>


////////////////////////////////
////// Class Point3d ///////////
////////////////////////////////

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
    os<<"( "<<u.x<<", "<<u.y<<", "<<u.z<<" )";
    return os ;
}