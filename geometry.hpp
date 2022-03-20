#ifndef geometry_hpp
#define geometry_hpp

#include <iostream>
#include <vector>
#include <cmath>

using namespace std ;

class Point
{
    public:
    double x,y;
    Point(double xi=0.,double yi=0.) :x(xi),y(yi){}
    Point& operator-=(const Point& P){
        x-=P.x;
        y-=P.y;
        return *this;
    }
    Point& operator+=(const Point& P){
        x+=P.x;
        y+=P.y;
        return *this;
    }
    Point& operator*=(double a){
        x*=a;
        y*=a;
        return *this;
    }
};
Point operator+(const Point& P1,const Point& P2);

Point operator-(const Point& P1,const Point& P2);

Point operator*(const Point& P, double a);
bool operator == (const Point& P1,const Point& P2);
bool operator != (const Point& P1,const Point& P2);
double distance(const Point& P1, const Point& P2);
ostream & operator <<(ostream &, const Point&);

class Segment
{
    public:
    Point P1, P2;
    Segment(const Point& pa=Point(),const Point& pb=Point());
    Segment& operator+=(const Point& P){
        P1+=P;
        P2+=P;
        return *this;
    }; //translation du segment dans la direction de P

};

bool operator ==(const Segment& , const Segment&);
Segment operator+(const Segment& S,const Point& P);

double produit_scalaire(const Segment& S1,const Segment& S2);
double produit_vectoriel(const Segment& S1,const Segment& S2);
double arclength(const Segment& S1,const Segment& S2);
double cos2deg(double angle);
double norme(const Segment& S1);
Segment normale_au_milieu(const Segment& S1);
Segment normale(const Segment& S1);
Segment normale_point(const Segment& S1,const Point& P);
Segment projection(const Point& P,const Segment& S);

bool point_segment(const Segment& S,const Point& P,double eps);
bool point_segment1(const Segment& S,const Point& P,double eps);
bool intersection_segment(const Segment& seg1,const Segment& seg2,double epsilon,double eps);

ostream & operator <<(ostream &, const Segment&);

class Obstacle
{
	public:
    int nbsom;
    vector<Point> sommets;
    Obstacle();
    Obstacle(int ns,const vector<Point> &obstacle_points); /*: n bsom(0){sommets=new Point[ns];}*/
    Obstacle(const Obstacle& ob);
    ~Obstacle();
    Obstacle& operator=(const Obstacle& ob);
    Obstacle& operator+=(Point& P);
    Obstacle& reset();
    vector<Segment> segments_of_obstacle() const;

};

ostream& operator<<(ostream& os,const Obstacle& ob);
vector<Point> normales_ext(const Obstacle& ob);
Obstacle transformation_padding(const Obstacle& Ob,double R);
double angle_normal(const Point& P);
#endif