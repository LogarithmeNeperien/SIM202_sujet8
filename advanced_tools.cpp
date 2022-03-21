#include "advanced_tools.hpp"

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

        //cout << cand1 << endl;
        //cout << "comptage = " << comptage << endl;

        if(comptage % 2 == 1)
        {
            normales.push_back( candidat1 * (1/norme(candidat1)) );
        }
        else
        {
            normales.push_back( candidat1 * (1/norme(candidat1)) );
        }

        //cout << *it << endl;
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