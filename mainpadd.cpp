#include "geometry.hpp" // points, segments, obstacles
#include "file_reader.hpp" // lecture du fichier texte
#include "write_graph.hpp" // écriture du graphe et chemin optimal
#include "graph.hpp" // validité des arcs et dijsktra
#include "padding.hpp" //padding circulaire
#include "advanced_tools.hpp" // normales, detection d'intersection..


int main(int argc,char** argv)
{
    // gestion du passage d'un fichier en ligne de commande
    char* nom_fichier;
    if (argc == 1)
    {
	    nom_fichier = (char*) "config/obs2.txt"; 
    } else 
    {
        nom_fichier = (char*) argv[1];
        cout << nom_fichier;
    }

    // rayon pour le padding
    double R = 0.5;
    // lecture du fichier retenu
    vector<Obstacle> vect_obst = reading(nom_fichier);

    // OBtention des points de départ et d'arrivée
    vector<Obstacle>::iterator it = vect_obst.begin();
    Point A((*it).sommets[0]);
    Point B((*it).sommets[1]);
    vect_obst.erase(it);
    //cout << vect_obst.size();

    // application de la transformation padding
    vector<Obstacle> vect_obs_padd = vector_obs_padding(vect_obst,R);

    Graph graphe = Graph(vect_obs_padd.size(),vect_obs_padd,A,B);

    // Ecriture du graphe dans un fichier texte
    write_graphe(graphe);

    // Recherche du plus cours chemin
    vector<Point> points_du_chemin = dijkstra(graphe);
    
    // Ecriture du chemin optimal
    write_optimal_path(points_du_chemin);

    return 0;

}