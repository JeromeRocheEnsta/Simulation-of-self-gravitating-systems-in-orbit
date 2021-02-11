#ifndef BOITE_H
#define BOITE_H

#include <iostream>
#include <list>

using namespace std;


// Class Point3d
class Point3d{
    public:
        double x;
        double y;
        double z;
        Point3d(double x0=0,double y0=0, double z0=0):x(x0),y(y0),z(z0){} //constructeur prenant deux coordonnées
        Point3d& operator +=(const Point3d & P){x+=P.x; y+=P.y; z=P.z; return *this;}
        Point3d& operator -=(const Point3d & P){x-=P.x; y-=P.y; z=P.z; return *this;}
        Point3d& operator *=(double a){x*=a; y*=a; z*=a;return *this;}
        Point3d& operator /=(double a){x/=a; y/=a; z/=a;return *this;}
};
Point3d operator + (const Point3d&, const Point3d&);
Point3d operator - (const Point3d&, const Point3d&);
Point3d operator * (double a, const Point3d&);
Point3d operator * (const Point3d&, double a);
Point3d operator / (double a, const Point3d&);
Point3d operator / (const Point3d&, double a);
bool operator == (const Point3d&, const Point3d&);
bool operator != (const Point3d&, const Point3d&);
ostream & operator <<(ostream & os ,const Point3d&);

//CLass Particule
class Particule
{
    public:
    double m;
    double r_x , r_y, r_z;
    double v_x , v_y , v_z;
    double F_x , F_y , F_z;

    Particule(double r_x_=0,double r_y_=0, double r_z_=0 ,double v_x_=0,double v_y_=0, double v_z_=0,double F_x_=0,double F_y_=0, double F_z_=0):
        r_x(r_x_),r_y(r_y_),r_z(r_z_),v_x(v_x_),v_y(v_y_),v_z(v_z_),F_x(F_x_),F_y(F_y_),F_z(F_z_){}

    void generateur();
    void initialisation (double);
    void mise_a_jour(double);
  
};

ostream & operator <<(ostream &,Particule&);



//CLass Boite
class Boite {
    public:
        int level;
        Point3d C; //Center
        double l; //length
        double w; //width
        double d; //depth
        Point3d G; //center of mass
        double m; //mass
        Particule * P; // Pointer on the only particule remaining in the boite
        Boite * sister; 
        Boite * child;
        //Constructeur
        Boite() {sister=NULL; child=NULL;};
        Boite(list<Particule> &){sister=NULL; child=NULL;};
        Boite(int lev, Point3d center, double length, double width, double depth){level= lev; C=center; l=length; w=width; d=depth;};
        //Method
        int check_number(list<Particule> &); // return number of particules in th boite
        void find_unique_child(list<Particule> &);
        void calculate_mass(list<Particule> &);
        void calculate_center_of_mass(list<Particule> &);
};

void create_graph(Boite *, list<Particule> &);

ostream & operator <<(ostream &,Boite&);
void print_graph(Boite *);
Boite first_box(list<Particule> &);
void force(Particule p, Boite& b, double M);




#endif
