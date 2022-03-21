#include "geometry.hpp"
#include <cmath>

/*
 CLASSE POINT 
*/
ostream& operator<<(ostream& os,const Point& point){
    os << "("<< point.x << "," << point.y << ")"<<endl;
    return os;
}

bool operator ==(const Point& point1,const Point& point2)
{
    if((point1.x==point2.x)&&(point1.y==point2.y))
    {
        return(true);
    }
    return(false);
}

bool operator !=(const Point& P1,const Point& P2)
{
    return !(P1 == P2);
}
Point operator+(const Point& P1,const Point& P2){
    Point Q(P1);
    Q+=P2;
    return Q;
}

Point operator-(const Point& P1,const Point& P2){
    Point Q(P1);
    Q-=P2;
    return Q;
}
Point operator*(const Point& P, double a){
    Point Q(P);
    Q*=a;
    return Q;
}
double distance(const Point& point1, const Point& point2)
{
    double distance;
    distance=(point1.x-point2.x)*(point1.x-point2.x)+(point1.y-point2.y)*(point1.y-point2.y);
    distance=sqrt(distance);
    return distance;
}

/*
 CLASSE SEGMENT 
*/

Segment::Segment(const Point& pa,const Point& pb)
{
    P1=pa;
    P2=pb;

}

bool operator==(const Segment& seg1, const Segment& seg2)
{
    bool c1 = (seg1.P1==seg2.P1) && (seg1.P2==seg2.P2);
    bool c2 = (seg1.P1==seg2.P2) && (seg1.P2 == seg2.P1);
    return ( c1 || c2 );
}

Segment operator+(const Segment& S,const Point& P){
    Segment T(S);
    T+=P;
    return T;
}

double produit_scalaire(const Segment& S1,const Segment& S2)
{
    Point P11=S1.P1;
    Point P12=S1.P2;
    Point P21=S2.P1;
    Point P22=S2.P2;

    double v1x=P11.x-P12.x;
    double v1y=P11.y-P12.y;
    double v2x=P21.x-P22.x;
    double v2y=P21.y-P22.y;
    double p=v1x*v2x+v1y*v2y;
    return(p);
}


double produit_vectoriel(const Segment& S1,const Segment& S2){
    Point P11=S1.P1;
    Point P12=S1.P2;
    Point P21=S2.P1;
    Point P22=S2.P2;

    double v1x=P11.x-P12.x;
    double v1y=P11.y-P12.y;
    double v2x=P21.x-P22.x;
    double v2y=P21.y-P22.y;

    double p=v1x*v2y-v1y*v2x;
    return p;
}

double norme(const Segment& S1)
{
    double N=produit_scalaire(S1,S1);
    N=sqrt(N);
    return(N);
}


double cos2deg(double angle){
    return acos(angle)*180/3.1415926535;
}

double arclength(const Segment& S1,const Segment& S2){
    return cos2deg(produit_scalaire(S1,S2)/(norme(S1)*norme(S2)));
}

Segment projection(const Point& P,const Segment& S){
    Segment rad(S.P1,P);
    Point vec(S.P2-S.P1);
    double scal = produit_scalaire(rad,S);
    double r = scal/(norme(S)*norme(S));
    Segment Proj(S.P1,S.P1+vec*r);
    return Proj;
}


ostream& operator<<(ostream& os,const Segment& seg){
    os << seg.P1 <<"-" << seg.P2 << endl;
    return os;
}

/*
 CLASSE OBSTACLE 
*/

Obstacle::Obstacle(){
    nbsom = 0;
    sommets = vector<Point>(0,Point());
}

Obstacle::Obstacle(int ns,const vector<Point> &obstacle_points){
    nbsom = ns;

    sommets=vector<Point>(0,Point());
    for(auto it = obstacle_points.begin();it != obstacle_points.end();++it){
        sommets.push_back(*it);
    }
}

Obstacle::Obstacle(const Obstacle& ob)
{
    nbsom = ob.nbsom;
    sommets=vector<Point>(0,Point());
    for(auto it = ob.sommets.begin();it != ob.sommets.end();++it){
        sommets.push_back(*it);
    }
}

Obstacle::~Obstacle()
{
    sommets.clear();
}

Obstacle& Obstacle::operator=(const Obstacle& ob)
{
    if (nbsom!=ob.nbsom)
    {
        nbsom=ob.nbsom;
        sommets.clear();
        sommets.resize(nbsom);
    }

    vector<Point>::iterator it = sommets.begin();
    vector<Point>::const_iterator it_ob;
    for(it_ob=ob.sommets.begin();it_ob != ob.sommets.end();it_ob++,it++) *it = *it_ob;
    return *this;
}

Obstacle& Obstacle::operator+=(Point& P){
    nbsom++;
    sommets.push_back(P);
    return *this;
}

Obstacle& Obstacle::reset(){
    nbsom=0;
    sommets.clear();
    return *this;
}

vector<Segment> Obstacle::segments_of_obstacle() const
{
    vector<Segment> segments;
    for(int i=0;i<nbsom-1;++i){
        segments.push_back(Segment(sommets[i],sommets[i+1]));
    }

    segments.push_back(Segment(sommets[nbsom-1],sommets[0]));

    return(segments);

}


ostream& operator<<(ostream& os,const Obstacle& ob){
    os << "Nb sommets = "<< ob.nbsom << endl;
    vector<Point>::const_iterator it_ob;
    for (it_ob = ob.sommets.begin(); it_ob != ob.sommets.end();++it_ob){
        os << *it_ob;
    }
    return os;
}
