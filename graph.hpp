#ifndef graph_hpp
#define graph_hpp

#include "geometry.hpp"

class Arc
{
  public :
    Segment edge;
    double length_arc;
    Arc(const Segment& S=Segment(),double Len=0);

};
ostream& operator<<(ostream& os,const Arc& A);

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

bool intersection_segment_polygon(const Segment& seg,const Obstacle& polygone);
int comptage_intersection(const Segment& seg,const Obstacle& obst);
bool intersection_segment(const Segment& seg1,const Segment& seg2, double epsilon,double eps);

ostream & operator <<(ostream &, const Graph &);

vector<Point> dijkstra(const Graph& graphe);

#endif