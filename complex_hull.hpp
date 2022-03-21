#ifndef complex_hull_hpp
#define complex_hull_hpp

#include "geometry.hpp"

// représente la coque d'un objet non circulaire
class complex_hull : public Obstacle {
    public :
    Point center;
    complex_hull():Obstacle(){
        Point center;
    }
    complex_hull(int nbsom);
    complex_hull(const complex_hull& CH):Obstacle(CH.nbsom,CH.sommets){
        center = CH.center;
    }
    complex_hull& operator=(const complex_hull& CH){
        Obstacle(CH.nbsom,CH.sommets);
        center = CH.center;
        return *this;
    }
    complex_hull& set_center(const Point& P){
        center = P;
        return *this;
    }
};

ostream& operator<<(ostream& os, const complex_hull& CH);

// list of radii between center and each vertex
vector<Segment> radii(const complex_hull& CH);

// list of corresponding sector length between pair of radii
vector<double> sector_length(const complex_hull& CH);

// find position of x in a vector of intervals
int is_in(double x,const vector<pair<double,double>>& mesh);

// find the index of the edge that meets the reference (0,0)-(1,0) 
int idx_ref(const complex_hull& CH);

// return the 0-360 angle mesh of internals angles, starting from ref
vector<pair<double,double>> sector_mesh(const complex_hull& CH);

// find which ede is concerned with the reference
int which_edge(const complex_hull& CH,double angle);

// compute radius of a CH in a given direction
double radius(const complex_hull& CH, double angle);


#endif