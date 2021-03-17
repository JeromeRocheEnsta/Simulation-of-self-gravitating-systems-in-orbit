#include "boite.hpp"
#include "math.h"
#include <list>


//////////////////////////////
///////Update du Graphe //////
//////////////////////////////
void is_particules_out(Boite & primal, list<Particule> & particules){
    /*
    Vient vérifier si les particules sont sortie de la boîte primal (principale)
    Entrée: La boîte primal ainsi que la liste de particules
    Sortie: Si une particule est sortie de la boîte primal, le graphe est refait de zéro.
    */

    //On teste qu'aucune particule sort du cadre.
    list<Particule>::iterator  it=particules.begin();
    for(; it!=particules.end(); it++){
        if( (it->r_x < primal.C.x - primal.w/2) || (it->r_x >= primal.C.x + primal.w / 2) || (it->r_y < primal.C.y - primal.l / 2) || (it->r_y >= primal.C.y + primal.l / 2) || (it->r_z < primal.C.z - primal.d / 2) || (it->r_z >= primal.C.z + primal.d / 2) ){
            Boite inter;
            inter = first_box(particules);
            Boite* primal_new = new Boite(inter);
            //clear le primal
            /* GROS PROBLEME DE GESTION DE MEMOIRE*/
            global_clear(&primal);
            primal = *primal_new;
            create_graph(&primal, particules);
            cout<<"Particule out"<<endl;
            return;
        }
    }
}

void eliminate_and_add_graph(Boite & primal, Boite & current,list<Particule> & particules){
    /*
    Fonction qui permet de parcourir le graphe à la recherche de boîte terminale contenant une particule. Si la particule
    est sortie de la boîte dans laquelle elle était à l'étape précédente, on fait appel à la fonction add et elimination.
    Entrée: 
        - primal qui permet d'appliquer la fonction add (qui effectuera un parcours du gaphe)
        - current qui permet de faire un parcours du graphe dans la fonction courante
        - particules la liste des particules permettant l'appel aux fonction add et elimination
    Sortie: Le graphe a été mis à jour pour convenir à la nouvelle disposition des particules
    */
    if(current.P != 0){
        
        if( (current.P->r_x < current.C.x - current.w / 2) || (current.P->r_x >= current.C.x + current.w / 2) || (current.P->r_y < current.C.y - current.l / 2) || (current.P->r_y >= current.C.y + current.l / 2) || (current.P->r_z < current.C.z - current.d / 2) || (current.P->r_z >= current.C.z + current.d / 2) ){
            add(primal, current.P, particules);
            elimination(current, particules);
            
        }
        if(current.sister != 0){
            eliminate_and_add_graph(primal, *current.sister, particules);
        }
    }
    else{
        if(current.child != 0){
            eliminate_and_add_graph(primal, *current.child, particules);
        }
        if(current.sister != 0){
            eliminate_and_add_graph(primal, *current.sister, particules);
        }
    }
}

void elimination(Boite & current,list<Particule> & particules){
    /*
    Permet de sortir la particule de son ancienne boîte terminale et de modifier le graphe en supprimant les boîtes qui n'ont 
    plus lieu d'être
    Entrée:
        - current qui permet un parcours du graphe en remontant
        - particules est la liste de particules nous permettant de modifier le graphe en le remontant grâce à la méthode
        check_number
    Sortie:
        La particule est éliminé de la boîte dans laquelle elle était et les boîtes devant être supprimé avec ce changement
        sont supprimées.
    */

    //On enlève le pointeur vers la particule
    current.P = 0;
    
    // On regarde le nombre d'enfant de la mère. Comme notre particule était dans une boîte de niveau supérieur la mère
    //avait forcément plus d'un enfant. Si elle n'en a plus qu'un il faut supprimer les enfants de cette boîte mère.
    
    if(current.mother->check_number(particules) == 1){
        //On trouve l'unique enfant et pointe la boîte mère vers la particule unique.
        current.mother->find_unique_child(particules);
        // Comme on supprime l'élément courant on ne pourra plus accéder à la mère par current->mother
        Boite & mother = *current.mother;
        global_clear(mother);

        //S'il y a une grand mère il va falloir regarder si elle aussi a plus d'un enfant sinon la mère n'a pas lieu d'être
        if(mother.mother != 0){
            //on réapplique ce principe jusqu'à trouver une boîte mère avec plusieurs particules.
            if(mother.mother->check_number(particules) == 1){
                elimination(mother, particules);
            }
        }
    }
}

void add(Boite & current, Particule* p, list<Particule> & particules){
    /*
    Permet d'ajouter la particule qui a changé de boîte dans le graphe et de le modifier en cas de besoin
    Entrée:
        -current permet de parcourir le graphe à la recherche d'une boîte contenant la particule à ajouter
        -p est notre particule a ajouter
        -particules est la liste de particules qui va servir à la construction de nouvelles boîte si la nouvelle boîte termianle
        dans laquelle a atterie la particule contenait déjà une particule.
    Sortie:
        Le graphe a été modifié
    */
    if(current.child != 0){
        add(*current.child, p, particules);
    }
    else{
        if( (p->r_x >= current.C.x - current.w / 2) && (p->r_x < current.C.x + current.w / 2) && (p->r_y >= current.C.y - current.l / 2) && (p->r_y < current.C.y + current.l / 2) && (p->r_z >= current.C.z - current.d / 2) && (p->r_z < current.C.z + current.d / 2) ){
            //La particule est dans cette boîte, on réutilise create_graph qui va créer des sous-boîtes en cas de besoin et y ajouter notre particule
            create_graph(&current ,particules);
        }
    }
    if(current.sister != 0){
        add(*current.sister, p, particules);
    }
}