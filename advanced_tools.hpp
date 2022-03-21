#ifndef advanced_tools_hpp
#define advanced tools_hpp
#include "geometry.hpp"


bool intersection_segment(const Segment& seg1,const Segment& seg2, double epsilon,double eps);

bool point_segment1(const Segment& S,const Point& P,double eps);

bool point_segment(const Segment& S,const Point& P,double eps);



Segment normale_au_milieu(const Segment& S1);


Segment normale_point(const Segment& S1,const Point& P);

Segment normale(const Segment& S1);
vector<Point> normales_ext(const Obstacle& ob);


double angle_normal(const Point& P);


#endif 