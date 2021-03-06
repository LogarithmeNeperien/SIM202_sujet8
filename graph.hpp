#ifndef graph_hpp
#define graph_hpp

#include "geometry.hpp"
#include "advanced_tools.hpp"

class Arc
{
  public :
    Segment edge;
    double length_arc;
    Arc(const Segment& S=Segment(),double Len=0);

};
ostream& operator<<(ostream& os,const Arc& A);

// Check if an edge intersect an obstacle
bool intersection_segment_polygon(const Segment& seg,const Obstacle& polygone);

// Check how many times an edge intersect the same obstacle
int comptage_intersection(const Segment& seg,const Obstacle& obst);

// Check if an edge is not going through any obstacle
bool is_arc_valide(const Segment& seg,const vector<Obstacle> & vect_obstacles, int nb_obstacles);


class Graph
{
    public:
    Arc * liste_arcs;
    Point * liste_sommets;
    int nb_arcs;
    int nb_sommets;

    Graph(int nb_Obstacles,const vector<Obstacle> & vect_obstacles,const Point& a, const Point& b);
    ~Graph();

};
ostream & operator <<(ostream &, const Graph &);

// Applies the standard Dijkstra algorithm
vector<Point> dijkstra(const Graph& graphe);

#endif