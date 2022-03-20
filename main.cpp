#include <iostream>
//#include "classe.hpp"
#include "geometry.hpp"
#include "file_reader.hpp"
#include "write_graph.hpp"
//#include "complex_hull.hpp"
#include "graph.hpp"
//#include "padding.hpp"

int main()
{

	//Point A = Point(0.5,2.5);
	//Point B = Point(6,4.5);

	Point C = Point(1.5,3.5);

	//double a=distance(P1,P2);
	//Segment S1=Segment(P2,P8);
	//Segment S2=Segment(P1,P2);

    //Segment test = Segment(A,C);

	char* nom_fichier = (char*) "config/obs2.txt"; // "..." de type string


	//cout << S1 << S2 << endl;
	//int m = 0;
	/*
	printf("P1.x vaut:%lf\n ",P1.x);
	double b=norme(S1);
	Point  LA[3]={P1,P2,P3};
	obstacle O(3,LA);
	affichage(O);
	O.add(P1);
	affichage(O);
	O.add(P2);
	O.add(P3);
	//obstacle G(O);
	printf("La distance entre les Points est de :%lf",a);
	printf("\n");
	printf("La norme du segement est :%lf\n",b);

	//affichage(G);
	printf("P1.x vaut:%lf\n ",P1.x);
	*/
	//affichage(S1);
	//Point_segment1(S1,P3,0.1);
	//Point_segment(S1,P3,0.1);
	//affichage(S2);
	//bool b=intersection_segment(S1,S2,0.1,0);
	//printf("%d\n",b);

    //vector<Point> liste_points = {P1,P2,P3,P4};
    //vector<Point> liste_points_2 = {P5,P6,P7,P8};

    //const Obstacle ob1 = Obstacle(4,liste_points);
    //const Obstacle ob2 = Obstacle(4,liste_points_2);

    //bool res = intersection_segment_polygon(S1,ob1);

    //cout << ob1 << ob2 << endl;
    double R = 1;
    vector<Obstacle> vect_obst = reading(nom_fichier);
    vector<Obstacle>::iterator it = vect_obst.begin();
    Point A((*it).sommets[0]);
    Point B((*it).sommets[1]);
    vect_obst.erase(it);
    //vector<Obstacle> vect_obst_padding = vector_obs_padding(vect_obst,R);
    const Obstacle ob1 = vect_obst[0];
    const Obstacle ob2 = vect_obst[1];
    const Obstacle ob3 = vect_obst[2];

    cout << ob1;
    cout << ob2;
    cout << ob3 << endl;

    //cout << vect_obst[0] << vect_obst[1] << vect_obst[2] << endl;


    Graph graphe = Graph(vect_obst.size(),vect_obst,A,B);
    //vector<Segment> segments  = ob2.segments_of_obstacle();



    //bool res = intersection_segment(test,segments[0],0.1,0);
    //cout << res << endl;
    write_graphe(graphe);

    cout << "bonjour ici" << endl;
    vector<Point> points_du_chemin = dijkstra(graphe);
    cout << "slt" << endl;
    write_optimal_path(points_du_chemin);


    //cout << graphe << endl;

    //cout << vect_obst[0] << vect_obst[1] << endl;


    //vector<Segment> segments  = ob.segments_of_obstacle();
    //cout << segments[0] << segments[1] << endl;

    /*
	Point liste_Points1[4] = {P1,P2,P3,P4};
	Point liste_Points2[4] = {P5,P6,P7,P8};


	obstacle test1 = obstacle(4,liste_Points1);
	obstacle test2 = obstacle(4,liste_Points2);
    affichage(test1);
    affichage(test2);
    */
    /*
    printf("m = %d",m);

    m = comptage_intersection(S1,test1);
    printf("m = %d",m);

    vector<int> test{1,2};
    printf("ca marche toujours\n");

    */
    /*
    obstacle* vect_obstacles = new obstacle[2];
    vect_obstacles[0] = test1;
    vect_obstacles[1] = test2;
    */


    //vector <obstacle> vect_obstacle;
    //vect_obstacle.push_back(test1);

    //vect_obstacles.push_back(test1);

    //printf("ca marche toujours\n");
    //bool valide;



    //valide = is_arc_valide(S2, vect_obstacles,2);
    //printf("valide = %d",valide);

    return 0;

}

