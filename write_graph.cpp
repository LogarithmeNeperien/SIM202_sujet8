#include "write_graph.hpp"
#include "file_reader.hpp" // for the libraries

void write_graphe(const Graph& graphe)
{
    ofstream myfile;
    myfile.open("graphe.txt");

    myfile << graphe.nb_arcs << "\n" << endl;

    for(int i=0;i<graphe.nb_arcs;++i)
    {
        myfile << graphe.liste_arcs[i].edge.P1.x << " " << graphe.liste_arcs[i].edge.P1.y << "\n";
        myfile << graphe.liste_arcs[i].edge.P2.x << " " << graphe.liste_arcs[i].edge.P2.y << "\n";
        myfile << graphe.liste_arcs[i].length_arc << "\n" << endl;
    }
    myfile.close();

}


void write_optimal_path(const vector<Point>& points_du_chemin)

{
    ofstream myfile;

    myfile.open("path.txt");

    vector<Point>::const_iterator it;

    myfile << points_du_chemin.size() << endl;

    for(it=points_du_chemin.begin();it!=points_du_chemin.end();++it)
    {
        myfile << (*it).x << " " << (*it).y << endl;
    }
    myfile.close();

}

void write_optimal_path_padd(const vector<Point>& points_du_chemin)
{
    ofstream myfile;
    myfile.open("path_padding.txt");

    vector<Point>::const_iterator it;

    myfile << points_du_chemin.size() << endl;

    for(it=points_du_chemin.begin();it!=points_du_chemin.end();++it)
    {
        myfile << (*it).x << " " << (*it).y << endl;
    }
    myfile.close();

}