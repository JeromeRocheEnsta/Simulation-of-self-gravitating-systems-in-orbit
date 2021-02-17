#include "boite.hpp"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

//////////////////////////////////
// Fonction Création des boîtes //
//////////////////////////////////

//Construction première boite

Boite first_box(list<Particule> & particules){
    /*
    Entrée: 
        particules: Liste des particules générés par les travaux de Aarseth, Henon et Wielen
    Sortie:
        Une boite primaire englobant toutes les particules. Elle est de niveau 1, centrée en 0
    */

    Boite B;
    B.level=1;
    list<Particule>::iterator it =particules.begin();
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
    B.l = 2*max_length + 2;
    B.w = 2*max_width+ 2;
    B.d= 2*max_depth + 2;
    B.calculate_mass(particules);
    B.calculate_center_of_mass(particules);
    B.P = NULL;
    return B;

};

//Création du graphe

void create_graph(Boite* current,list<Particule> & particules){
    /*
    Entrée: 
        current: Boite que l'on est en train de considérer
        particules: Liste des particules générés par les travaux de Aarseth, Henon et Wielen
    Sortie:
        Si la boîte d'entrée n'est pas terminale, on crée ses enfants et on réapplique la fonction à ses enfants
        Sinon on détermine la particule liée à la boîte (si elle existe)
        Dans tous les cas si la boïte d'entrée à une soeur on applique la fonction à la soeur
    */

    //On profite de commencer par trouver m et G
    current->calculate_mass(particules);
    current->calculate_center_of_mass(particules);
    
    //Corps de la fonction
    if(current->check_number(particules)==0){
        current->P = NULL;
        if(current->sister != 0){
            create_graph( current->sister, particules);
        }
    }
    else if(current->check_number(particules)==1){
        current->find_unique_child(particules);
        if(current->sister != 0){
            create_graph( current->sister, particules);
        }
    }else{
        //Créer les enfants
        double w = current->w;
        double l = current->l;
        double d = current->d;
        Point3d C = current->C;
        Point3d P(C.x - w/4, C.y + l/4,C.z - d/4),Q(C.x + w/4, C.y + l/4, C.z - d/4),R(C.x + w/4, C.y - l/4, C.z - d/4),S(C.x - w/4, C.y - l/4, C.z - d/4),T(C.x - w/4, C.y + l/4,C.z + d/4),U(C.x + w/4, C.y + l/4, C.z + d/4),V(C.x + w/4, C.y - l/4, C.z + d/4),W(C.x - w/4, C.y - l/4, C.z + d/4);
        current->child = new Boite(current->level + 1, P, l/2, w/2, d/2 );
        current->child->sister = new Boite(current->level + 1, Q, l/2, w/2, d/2 );
        current->child->sister->sister = new Boite(current->level + 1, R, l/2, w/2, d/2 );
        current->child->sister->sister->sister = new Boite(current->level + 1, S, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister = new Boite(current->level + 1, T, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister->sister = new Boite(current->level + 1, U, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister->sister->sister = new Boite(current->level + 1, V, l/2, w/2, d/2 );
        current->child->sister->sister->sister->sister->sister->sister->sister = new Boite(current->level + 1, W, l/2, w/2, d/2 );
        //Appliquer la fonction à la soeur et à la première fille
        if(current->sister != 0){
            create_graph( current->sister, particules);
        }
        create_graph( current->child, particules);
    }
}


////////////////////////////////
//////// Classe Boite //////////
////////////////////////////////

int Boite::check_number(list<Particule> & particules){
    /*
    Permet de checker le nombre de particule de particules contenu dans la boite et le retourne
    */
    int compteur=0;
    list<Particule>::iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            compteur++;
        }
    }
    return compteur;
}

void Boite::find_unique_child(list<Particule> & particules){
    /*
    Dans le cas où check_number renvoie 1, on trouve l'unique particule pour la lier à la boîte
    */
    list<Particule>::iterator it =particules.begin();

    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            P= &*it;
        }
    }
}

void Boite::calculate_mass(list<Particule> & particules){
    /*
    Permet de calculer la masse totale d'une boîte
    Attention: elle vaut zéro si aucune particule dans la boîte
    */

    m=0;
    list<Particule>::iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            m+= it->m;
        }
    }
}

void Boite::calculate_center_of_mass(list<Particule> & particules){
    /*
    Permet de calculer le centre de masse d'une boîte
    Attention: il est calibré à l'origine si aucune particules dans la boîte
    */

    G.x=0;
    G.y=0;
    G.z=0;
    list<Particule>::iterator it = particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x >= C.x - w/2) && (it->r_y >= C.y - l/2) && (it->r_x < C.x + w/2) && (it->r_y < C.y + l/2) && (it->r_z >= C.z - d/2) && (it->r_z < C.z + d/2)){
            G.x += it->m*it->r_x;
            G.y += it->m*it->r_y;
            G.z += it->m*it->r_z;
        }
    }
    // Dans certains cas la masse peut être nulle
    if(m != 0){
        G/=m;
    }
}

void print_graph(Boite * current){
    if(current->child != 0){
        print_graph(current->child);
    }
    else{
        cout<<*current<<endl;
    }

    if(current->sister != 0){
        print_graph(current->sister);
    }
}


ostream & operator<< (ostream & os, Boite& B){
    os<<"Niveau:("<<B.level<<") / Centre:("<<B.C.x<<","<<B.C.y<<","<<B.C.z<<") / largeur:("<<B.w<<") /  longueur:("<<B.l<<") / Profondeur:("<<B.d<<") \n";
    return os;
}


////////////////////////////////
////// Calcul des forces ///////
////////////////////////////////


void all_force(Boite * current, Boite * primal){
    /*
    Entrée: 
        current: est la boîte que l'on traite
        primal: c'est la boite de niveau 1, on en aura besoin dans le calcul de force afin de parcourir le graph
    Sortie:
        Après avoir appliqué cette fonction, on aura calculé toutes les forces gravitationnelle s'appliquant sur toutes nos particules.
        Etape nécessaire pour faire évoluer notre système
    */

    // Si c'est une boite terminale avec particule on calcul la force qui s'exerce sur cette particule
    if(current->P != 0){
        force(current, primal);
    }
    // Si c'est pas une boite terminale on parcourt sa fille
    if(current-> child != 0){
        all_force(current->child, primal);
    }
    // Si elle aune soeur on la parcourt aussi
    if(current->sister != 0){
        all_force(current->sister, primal);
    }
}


void force(Boite * current, Boite * primal){
     /*
    Entrée: 
        current: est la boîte - contenant une et une seule particule - que l'on traite
        primal: c'est la boite de niveau 1, on en aura besoin afin de parcourir le graph
    Sortie:
        Calcul de la force gravitationnelle s'appliquant à la particule contenu dans current.
    */

    //Calcul de nos constantes
    const double G= 6.6742*pow(10,-11);
    const double epsilon = min(current->l,min(current->w,current->d))/100;

    //Parcourir le graph mais la question c'est comment ?
    //Pour chaque boite du graph, si la boite est de même niveau que current->level on calcul la force qui s'exerce et on ne considère pas les boites filles
        //On ajoute la contribution à la force gravitationnelle

   

}




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
    os<<"( "<<u.x<<", "<<u.y<<" )";
    return os ;
}
