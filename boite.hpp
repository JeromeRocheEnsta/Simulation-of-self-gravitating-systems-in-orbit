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

    Particule(double m = 0,double r_x_=0 ,double r_y_=0, double r_z_=0 , double v_x_=0,double v_y_=0, double v_z_=0,double F_x_=0,double F_y_=0, double F_z_=0):
        m(m),r_x(r_x_),r_y(r_y_),r_z(r_z_),v_x(v_x_),v_y(v_y_),v_z(v_z_),F_x(F_x_),F_y(F_y_),F_z(F_z_){}

    void initialisation();
    void mise_a_jour();
  
};

list<Particule> generateur_plummer(double N, double M, double E, double R, double mu, double omega, bool circ = false);
void Plummer_circ(list<Particule>& particules, double R, double M,double omega, double mu);
ostream & operator <<(ostream &,Particule&);
void affichage_by_step(list<Particule>, int ); //Il nous permettra d'afficher l'état de notre sysytème à chaque itérations 



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
        Boite * mother;
        //First Box
        //Constructeur
        Boite() {sister=NULL; child=NULL; mother=NULL;};
        Boite(list<Particule> & particules){sister=NULL; child=NULL; mother= NULL;};
        Boite(int lev, Point3d center, double length, double width, double depth, Boite* mother = NULL){level= lev; C=center; l=length; w=width; d=depth; mother = mother;};
        //Constructeur par copie
        Boite(const Boite & b){level = b.level; C = b.C; l= b.l; w=b.w; d=b.d; mother=b.mother; G= b.G; m= b.m; P= b.P; sister= b.sister; child= b.child;};
        //Destructeur
        ~Boite(){
            delete sister;
            sister = 0;
            delete child;
            child = 0;
            P = 0;
            mother = 0;
        };
        //Method
        int check_number(list<Particule> &); // return number of particules in th boite
        void find_unique_child(list<Particule> &);
        void calculate_mass(list<Particule> &);
        void calculate_center_of_mass(list<Particule> &);
        void clear() {
            delete[] sister;
            sister =NULL;
            delete[] child;
            child =NULL;
            delete[] P;
            P=NULL;
        };
};

void create_graph(Boite *, list<Particule> &);

ostream & operator <<(ostream &,Boite&);
void print_graph(Boite *);
// Modifier son contenu vers le constructeur de Boite 
Boite first_box(list<Particule> &);

//Calcul de la force
void force(Particule &, Boite* );
void all_forces(Boite *, Boite *);
void calculate_forces(Boite *, Boite *, list<Particule> &, double omega, bool);

void global_initialisation(list<Particule>&);
void global_update(list<Particule>&);
void global_clear(Boite *);
void global_clear(Boite &);
//Graph update
void is_particules_out(Boite &, list<Particule> &);
void eliminate_and_add_graph(Boite &, Boite & ,list<Particule> & );
void elimination(Boite & current,list<Particule> & particules);
void add(Boite &, Particule *, list<Particule> & particules);
#endif
