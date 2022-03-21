#include <iostream>

#include "geometry.hpp" // points, segments, obstacles, normales...

#include "file_reader.hpp" // lecture du fichier texte
#include "write_graph.hpp" // écriture du graphe et chemin optimal
//#include "complex_hull.hpp" //padding à géométrie variable
#include "graph.hpp" // validité des arcs et dijsktra
//#include "padding.hpp" //padding circulaire
#include "advanced_tools.hpp"
#include <typeinfo>

int main(int argc,char** argv)
{

    char* nom_fichier;
    if (argc == 1)
    {
	    nom_fichier = (char*) "config/obs2.txt"; 
    } else 
    {
        nom_fichier = (char*) argv[1];
        cout << nom_fichier;
    }
    vector<Obstacle> vect_obst = reading(nom_fichier);
    vector<Obstacle>::iterator it = vect_obst.begin();
    Point A((*it).sommets[0]);
    Point B((*it).sommets[1]);
    vect_obst.erase(it);


    Graph graphe = Graph(vect_obst.size(),vect_obst,A,B);
 
    write_graphe(graphe);

    vector<Point> points_du_chemin = dijkstra(graphe);
    
    write_optimal_path(points_du_chemin);

    return 0;

}

