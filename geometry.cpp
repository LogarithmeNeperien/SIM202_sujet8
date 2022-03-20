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

//a regarder
/*
segment* obstacle ::liste_segment()
{
    segment* liste_arretes=new segment[nbsom];


    for(int i=0;i<nbsom-1;++i){
        liste_arretes[i] = segment(sommets[i],sommets[i+1]);

    }

    liste_arretes[nbsom-1]=segment(sommets[nbsom-1],sommets[0]);
    return(liste_arretes);
}
*/

Segment normale_au_milieu(const Segment& S1)
{
    Point P1=S1.P1;
    Point P2=S1.P2;
    double x_M=(P1.x+P2.x)/2;
    double y_M=(P1.y+P2.y)/2;
    double x_N=P2.y-P1.y+x_M;
    double y_N=P1.x-P2.x+y_M;
    Point M=Point(x_M,y_M);
    Point N=Point(x_N,y_N);
    Segment A=Segment(M,N);
    return(A);
}

Segment normale_point(const Segment& S1,const Point& P)
{
    Point P1=S1.P1;
    Point P2=S1.P2;
    if(P2 == P)
    {
        P2=P1;
        P1=P;
    }
    double x_M=P1.x;
    double y_M=P1.y;
    double x_N=P2.y-P1.y+x_M;
    double y_N=P1.x-P2.x+y_M;
    Point M=Point(x_M,y_M);
    Point N=Point(x_N,y_N);
    Segment A=Segment(M,N);
    return(A);
}

Segment normale(const Segment& S1)
{
    Point P1=S1.P1;
    Point P2=S1.P2;
    double x_M=P1.x;
    double y_M=P1.y;
    double x_N=P2.y-P1.y+x_M;
    double y_N=P1.x-P2.x+y_M;
    Point M=Point(x_M,y_M);
    Point N=Point(x_N,y_N);
    Segment A=Segment(M,N);
    return(A);
}

bool point_segment(const Segment& S,const Point& P,double eps)
{
    Segment S1=Segment(S.P1,P);
    double projete=produit_scalaire(S,S1)/(norme(S));
    double x_E=S.P1.x+projete*(S.P2.x-S.P1.x)/norme(S);
    double y_E=S.P1.y+projete*(S.P2.y-S.P1.y)/norme(S);
    Point E=Point(x_E,y_E);
    //cout << S << "norme : " << norme(S) <<endl;
    //cout << E << endl;
    double d=distance(E,P);
    //printf("d vaut %lf\n",d);
    if(d<=eps)
    {
        double MIN=min(S.P1.x,S.P2.x)-eps;
        double MAX=max(S.P1.x,S.P2.x)+eps;
        if((MIN<=x_E)&&(MAX>=x_E))
        {
            //printf("Le Point est dans le segment\n");
            return(true);
        }
    }
    //printf("Le Point n'est pas dans le segment\n");
    return(false);
}

bool point_segment1(const Segment& S,const Point& P,double eps)
{
    double a=(S.P1.y-S.P2.y)/(S.P1.x-S.P2.x);
    double b=a*S.P1.x-S.P1.y;
    if((a*P.x+b+eps>=P.y)&(a*P.x+b-eps<=P.y))
        {
        double MIN=min(S.P1.y,S.P2.y)-eps;
        double MAX=max(S.P1.y,S.P2.y)+eps;
        if((MIN<=P.y)&&(MAX>=P.y))
        {
            printf("Le Point est dans le segment\n");
            return(true);
        }

         }
    printf("Le Point n'est pas dans le segment\n");
    return(false);
}
//true si les segments s'intersectent et false sinon
bool intersection_segment(const Segment& seg1,const Segment& seg2, double epsilon,double eps)
{    
    Point point_a = seg1.P1;
    Point point_b = seg1.P2;
    Point point_p = seg2.P1;
    Point point_q = seg2.P2;

    if(  (point_a == point_p) || (point_a == point_q) || (point_b == point_p) || (point_b == point_q) )
    {
        return false;
    }
    if(  abs( produit_scalaire(seg1,seg2) - norme(seg1)*norme(seg2) ) == 0 )
    {
        //cout << seg1;
        //cout << seg2;
        if(point_segment(seg2,point_a,epsilon) || point_segment(seg2,point_b,epsilon) ) //il n'y avait pas d'argument epsilon
        {
            return true;
        }
        else{return false;}
    }
    Segment segment_ab=Segment(point_a,point_b);
    Segment segment_pq=Segment(point_p,point_q);
    Segment normale_ab = normale(segment_ab);
    Segment normale_pq = normale(segment_pq);

    Segment segment_pa=Segment(point_p,point_a);
    Segment segment_ap=Segment(point_a,point_p);

    double alpha = produit_scalaire(segment_ap,normale_pq) / produit_scalaire(segment_ab,normale_pq);
    double beta = produit_scalaire(segment_pa,normale_ab) / produit_scalaire(segment_pq,normale_ab);

    if( (-eps <= alpha) && (alpha <= 1+eps) && (-eps <= beta) && (beta<= 1+eps))
    {
        /*
        printf("alpha = %lf\n",alpha);
        printf("%beta = %lf\n",beta);
        printf("Les deux segments s'intersectent\n");
        */
        return true;
    }
    else
    {
        /*
        printf("alpha = %lf\n",alpha);
        printf("%beta = %lf\n",beta);
        printf("Les deux segments ne s'intersectent pas\n");
        */
        return false;
    }

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

/*
Obstacle::Obstacle(const Obstacle& ob)
{
    nbsom=ob.nbsom;
    sommets=vector<Point>(0,Point());
    for(auto it = Ob.sommets.begin();it != Ob.sommets.end();++it){
        sommets.push_back(*it);
    }
}
*/

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

vector<Point> normales_ext(const Obstacle& ob)
{
    const vector<Segment> segments = ob.segments_of_obstacle();
    vector<Point> normales;

    vector<Segment>::const_iterator it;


    for(it=segments.begin();it!=segments.end();++it)
    {
        Segment normale_non_translate = normale_au_milieu(*it);

        Point point_sur_segment;

        if( point_segment(*it,normale_non_translate.P1,0.01) )
        {
            point_sur_segment = normale_non_translate.P1;
        }
        else
        {
            point_sur_segment = normale_non_translate.P2;
        }

        Point candidat1 = normale_non_translate.P2 - normale_non_translate.P1;
        Point candidat2 = normale_non_translate.P1 - normale_non_translate.P2;

        Point test_cand1 = (candidat1 * 100) + point_sur_segment;
        Point test_cand2 = (candidat2 * 100) + point_sur_segment;

        Segment cand1 = Segment( point_sur_segment , test_cand1 );
        Segment cand2 = Segment( point_sur_segment, test_cand2 );


        int comptage = 0;

        for(int i=0;i<ob.nbsom;++i)
        {
            if( intersection_segment(cand1,segments[i],0.1,0.)  )
            {
                comptage++;
            }
        }

        cout << cand1 << endl;
        cout << "comptage = " << comptage << endl;

        if(comptage % 2 == 1)
        {
            normales.push_back( candidat1 * (1/norme(candidat1)) );
        }
        else
        {
            normales.push_back( candidat1 * (1/norme(candidat1)) );
        }

        cout << *it << endl;
    }


    return(normales);
}


double angle_normal(const Point& P){
    double a = P.x;
    double b = P.y;
    double offset = 0;
    if (b < 0) offset = 180;
    if (a == 0) return 90+offset;
    double angle = (180/3.14159265)*atan(b/a)+offset;
    return angle;
}