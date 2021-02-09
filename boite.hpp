#ifndef BOITE_H
#define BOITE_H

#include <iostream>
#include <list>

using namespace std;


// Class Point2d
class Point2d{
    public:
        double x;
        double y;
        Point2d(double x0=0,double y0=0):x(x0),y(y0){} //constructeur prenant deux coordonnées
        Point2d& operator +=(const Point2d & P){x+=P.x; y+=P.y; return *this;}
        Point2d& operator -=(const Point2d & P){x-=P.x; y-=P.y; return *this;}
        Point2d& operator *=(double a){x*=a; y*=a; return *this;}
        Point2d& operator /=(double a){x/=a; y/=a; return *this;}
};
Point2d operator + (const Point2d&, const Point2d&);
Point2d operator - (const Point2d&, const Point2d&);
Point2d operator * (double a, const Point2d&);
Point2d operator * (const Point2d&, double a);
Point2d operator / (double a, const Point2d&);
Point2d operator / (const Point2d&, double a);
bool operator == (const Point2d&, const Point2d&);
bool operator != (const Point2d&, const Point2d&);
ostream & operator <<(ostream & os ,const Point2d&);

//CLass Particule
class Particule
{
    public:
    double r_x , r_y, r_z;
    double v_x , v_y , v_z;
    double F_x , F_y , F_z;

    Particule(double r_x_=0,double r_y_=0, double r_z_=0 ,double v_x_=0,double v_y_=0, double v_z_=0,double F_x_=0,double F_y_=0, double F_z_=0):
        r_x(r_x_),r_y(r_y_),r_z(r_z_),v_x(v_x_),v_y(v_y_),v_z(v_z_),F_x(F_x_),F_y(F_y_),F_z(F_z_){}

    void generateur();
    //void force(Boite& );
    void initialisation ();
    void mise_a_jour();
  
};

ostream & operator <<(ostream &,const Particule&);



//CLass Boite
class Boite {
    public:
        int level;
        Point2d C; //Center
        double l; //length
        double w; //width
        Point2d G; //center of mass
        double m; //mass
        Particule * P; // Pointer on the only particule remaining in the boite
        Boite * sister; 
        Boite * child;
        //Constructeur
        Boite() {sister=NULL; child=NULL;};
        Boite(const list<Particule> &){sister=NULL; child=NULL;};
        Boite(int lev, Point2d center, double length, double width){level= lev; C=center; l=length; w=width; sister=NULL; child=NULL;};
        //Method
        int check_number(const list<Particule> &); // return number of particules in th boite
        void find_unique_child(const list<Particule> &);
        //void calculate_mass(const list<Particule> &);
        //void calculate_center_of_mass(const list<Particule> &);
        list<Point2d> find_new_centers();
};

void create_graph(Boite &, const list<Particule> &);








#endif