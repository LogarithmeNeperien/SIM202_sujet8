#include <cstdlib>
#include <cmath>
#include <vector >
#include <limits>
#include <algorithm>
#include "classe.hpp"

using namespace std ;


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

Point operator + (const Point& P1,const Point& P2)
{
    Point somme;
    somme.x = P1.x + P2.x;
    somme.y = P1.y + P2.y;
    return somme;
}

Point operator - (const Point& P1,const Point& P2)
{
    Point diff;
    diff.x = P1.x - P2.x;
    diff.y = P1.y - P2.y;
    return diff;
}

Point operator*(const Point & P, double u)
{
    Point mult;
    mult.x = P.x * u;
    mult.y = P.y*u;

    return mult;
}

double distance(const Point& point1, const Point& point2)
{
    double distance;
    /*
    printf("P1.x :%lf\n",P1.x);
    printf("P2.x :%lf\n",P2.x);
    printf("P1.y :%lf\n",P1.y);
    printf("P2.y :%lf\n",P2.y);
    */
    distance=(point1.x-point2.x)*(point1.x-point2.x)+(point1.y-point2.y)*(point1.y-point2.y);
    distance=sqrt(distance);
    return distance;
}

double norme(const Point& P)
{
    return sqrt( (P.x)*(P.x) + (P.y)*(P.y) );
}


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

Segment operator+(const Segment& seg,const Point& P)
{
    Segment translate;
    translate.P1 = seg.P1 + P;
    translate.P2 = seg.P2 + P;

    return translate;
}

Segment operator-(const Segment& seg,const Point& P)
{
    Segment translate;
    translate.P1 = seg.P1 - P;
    translate.P2 = seg.P2 - P;

    return translate;
}

Segment operator*(const Segment& seg, double u)
{
    Segment mult;


}

double produit_scalaire(const Segment& S1,const Segment& S2)
{
    Point P11=S1.P1;
    double P11x=S1.P1.x;
    Point P12=S1.P2;
    Point P21=S2.P1;
    Point P22=S2.P2;

    double v1x=P11.x-P12.x;
    double v1y=P11.y-P12.y;
    double v2x=P21.x-P22.x;
    double v2y=P21.y-P22.y;
    /*
    printf("P11.x :%lf\n",P11.x);
    printf("P11x :%lf\n",P11x);
    printf("v1x: %lf \n",v1x);
    printf("v2x: %lf \n",v2x);
    printf("v1y:%lf \n",v1y);
    printf("v2y:%lf \n",v2y);
    */
    double p=v1x*v2x+v1y*v2y;
    return(p);
}

double norme(const Segment& S1)
{
    double N=produit_scalaire(S1,S1);
    N=sqrt(N);
    return(N);
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
/*
Segment translater_exterieur(const Segment& seg, double r,const Obstacle& ob)
{
    Segment normale_milieu = normale_au_milieu(seg);
    Point normale_ext = normale_milieu.P2 - normale_milieu.P1;
    //on a récupéré la normale extérieur

    Point normalise_normale_ext;
    normalise_normale_ext = normale_ext * (1/norme(normale_ext));


    Segment trans_ext_sens_1;
    trans_ext_sens_1.P1 = seg.P1 + normalise_normale_ext*r;
    trans_ext_sens_1.P2 = seg.P2 + normalise_normale_ext*r;

    Segment trans_ext_sens_2;
    trans_ext_sens_1.P1 = seg.P1 + normalise_normale_ext*(-r);
    trans_ext_sens_2.P2 = seg.P2 + normalise_normale_ext*(-r);




    return trans_ext;


}
*/

ostream& operator<<(ostream& os,const Segment& seg){
    os << "Le premier point du segment est : "<< seg.P1 << endl;
    os << "Le deuxième point du segment est : " << seg.P2 <<endl;
    return os;
}

//=========================================================================
//Obstacle
//=========================================================================

/*
Obstacle::Obstacle(){
    nbsom = 0;
    sommets = vector<Point>(0,Point());
}
*/

Obstacle::Obstacle(int ns,const vector<Point> &obstacle_points){
    nbsom = ns;

    sommets = obstacle_points;
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
    sommets = ob.sommets;
}


Obstacle::~Obstacle()
{
    sommets.clear();
    nbsom = 0;
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

/*
void affichage(const obstacle& Ob)
{
    int nbsom=Ob.nbsom;
    Point * sommets=Ob.sommets;
    printf("Il y a  %d sommets\n",nbsom);
    for(int i=0;i<nbsom;i++) {
        printf("le sommet %d est :(%lf,%lf)\n",i,sommets[i].x,sommets[i].y);
    }
}
*/




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
            if( intersection_segment(cand1,segments[i],0.1,0)  )
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

int comptage_intersection(const Segment& seg,const Obstacle& obst)
{

    Point p1 = seg.P1;
    Point p2 = seg.P2;
    double x_M = (p1.x+p2.x)/2;
    double y_M = (p1.y+p2.y)/2;
    Point M = Point(x_M,y_M);
    double x_M1 = x_M + 100;
    Point M1 = Point(x_M1,y_M);
    Segment seg_milieu = Segment(M,M1);
    int comptage_intersect = 0;

    const vector<Segment> segments_obst = obst.segments_of_obstacle();


    for(int i=0;i<obst.nbsom;++i)
    {
        //&& !(point_segment(seg_milieu,segments_obst[i].P2,0))
        //on regarde si le segment prolongé a tapé un agnle
        if( intersection_segment(seg_milieu,segments_obst[i],0.1,0)  && !(point_segment(seg_milieu,segments_obst[i].P2,0)) )
        {
            comptage_intersect++;
        }
    }
    return comptage_intersect;

}

//renvoie true si le segment est valide par rapport à l'obstacle passé en paramètre
bool intersection_segment_polygon(const Segment& seg,const Obstacle& polygone)
{
    const vector<Segment> segments = polygone.segments_of_obstacle();
    vector<Segment>::const_iterator it;

    //on compte le nombre de coins d'obstacle qui correspondent aux etremites du segment
    //si 2 alors le segment est soit une diagonale du polygone au sens large
    //dans ce cas on s'il passe le premier test, on appelle comptage
    //intersection
    int nombre_coins_obstacle = 0;

    for(it=segments.begin();it!=segments.end();++it)
    {
        if( (seg.P1==(*it).P1) || (seg.P1==(*it).P2) || (seg.P2==(*it).P1) || (seg.P2==(*it).P2) )
        {
            nombre_coins_obstacle++;
        }

        if(intersection_segment(seg,*it,0.1,0))
        {
            return false;
        }
        if(seg == *it)
        {
            return true;
        }
    }

    if(nombre_coins_obstacle == 4)
    {
        int nombre_intersection_projete_milieu = comptage_intersection(seg,polygone);

        if(nombre_intersection_projete_milieu % 2 != 0)
        {
            return false;
        }
    }

    return true;

}

Arc::Arc(const Segment& S,double Len)
{
    edge = S;
    length_arc = Len;
}

ostream& operator <<(ostream& os,const Arc& A){
    os << A.edge <<  " : length = " <<  A.length_arc << endl;
    return os;
}

bool is_arc_valide(const Segment& seg,const vector<Obstacle> & vect_obstacles, int nb_obstacles)
{

    vector<Obstacle>::const_iterator it;
    for(it=vect_obstacles.begin();it != vect_obstacles.end();++it)
    {

        if(!intersection_segment_polygon(seg, *it))
        {
            return false;
        }
    }

    return true;
}

Graph::Graph(int nb_obstacles ,const vector<Obstacle> & vect_obstacles,const Point& a, const Point& b)
{
    liste_sommets = new Point[500];
    int m = 0;
    int nbr_arcs_crees = 0;

    vector<Obstacle>::const_iterator it_ob;

    liste_sommets[m] = a;
    m++;

    for(it_ob=vect_obstacles.begin();it_ob!=vect_obstacles.end();++it_ob)
    {
        for(int i = 0; i<(*it_ob).nbsom;++i)
        {
            liste_sommets[m] = (*it_ob).sommets[i];
            m++;
        }
    }
    liste_sommets[m] = b;
    m++;
    nb_sommets = m;

    liste_arcs = new Arc[(m*(m-1))/2];
    nb_arcs = (m*(m-1)/2);
    double length_p_k = 0;


    it_ob = vect_obstacles.begin();

    for(int k=0;k<m;++k)
    {
        for(int p=k+1;p<m;++p)
        {
            const Segment segment_p_k = Segment(liste_sommets[k],liste_sommets[p]);

            if(is_arc_valide(segment_p_k,vect_obstacles,nb_obstacles))
            {
                Point p_k = liste_sommets[k];
                Point p_p = liste_sommets[p];
                length_p_k = distance(p_k,p_p);
            }
            else
            {
                length_p_k = -1;
            }
            //cout << segment_p_k << " distance : " << length_p_k;
            liste_arcs[nbr_arcs_crees] = Arc(Segment(liste_sommets[k],liste_sommets[p]),length_p_k);
            nbr_arcs_crees++;


        }
    }

}


Graph::~Graph()
{
    if(liste_sommets != 0)  delete [] liste_sommets;
    if(liste_arcs != 0)  delete [] liste_arcs;
}


ostream & operator <<(ostream &os , const Graph &g)
{
    os << "affichage de tous les arcs :\n";
    for(int i=0; i<g.nb_arcs ; i++)
    {
       os<< g.liste_arcs[i] << endl;
    }
    return os ;
}

vector<Obstacle> reading(char* nom_fichier){
	vector<Obstacle> list_obstacles;
	Obstacle ob(0,{});
	ifstream infile(nom_fichier);
	string line;
	string obs("/");
	string comment("%");
	string end("#");
	int nb_obs = 0;
	double a,b;
	while(getline(infile,line))
	{
		if (line[0] == obs[0]){
			nb_obs++;
			list_obstacles.push_back(ob);
			ob.reset();
			continue;
		}
		if (line[0] == comment[0]){
			continue;
		}
		if (line[0] == end[0]){
			break;
		}
		istringstream iss(line);
		iss >> a >> b;
		Point p(a,b);
		ob+=p;
	}
	list_obstacles.push_back(ob);
	infile.close();
	printf("fin lecture \n");

	return list_obstacles;
}

void write_graphe(const Graph& graphe)
{
    ofstream myfile;
    myfile.open("graphe3.txt");

    myfile << graphe.nb_arcs << "\n" << endl;

    for(int i=0;i<graphe.nb_arcs;++i)
    {
        myfile << graphe.liste_arcs[i].edge.P1.x << " " << graphe.liste_arcs[i].edge.P1.y << "\n";
        myfile << graphe.liste_arcs[i].edge.P2.x << " " << graphe.liste_arcs[i].edge.P2.y << "\n";
        myfile << graphe.liste_arcs[i].length_arc << "\n" << endl;
    }
    myfile.close();

}


vector<Point> dijkstra(const Graph& graphe)
{
    int n = graphe.nb_sommets;
    double inf = std::numeric_limits<double>::infinity();

    vector <vector <double> > c(n, vector<double>(n,inf));

    for (int i=0; i<n; ++i)
    {
        for(int j=i+1;j<n;++j)
        {
            int k = (n-1)*i - i*(i+1)/2 + j - 1;
            double val;
            if( graphe.liste_arcs[ k ].length_arc == -1 )
            {
                val = inf;
            }
            else
            {
                val = graphe.liste_arcs[ k ].length_arc;
            }
            c[i][j] = val;
            c[j][i] = val;
        }
    }

    vector<double> l = c[0];

    vector<Point> p(n,Point());

    for(int j=1;j<n;++j)
    {
        if( c[0][j] < inf )
        {
            p[j] = graphe.liste_sommets[0];
        }
    }

    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }


    vector<Point> S(n,Point());
    S[0] = graphe.liste_sommets[0];

    vector<Point> T;
    for(int j=1;j<n;++j)
    {
        T.push_back(graphe.liste_sommets[j]);
    }




    while( !T.empty() )
    {
          //vector<double>::iterator i_min = min_element(l.begin(),l.end());

          //int i = distance(l.begin(), i_min);

          double l_min = inf;
          int i_min = -1;

          for(int i=0;i<n;++i)
          {
            if(  find(T.begin(),T.end(), graphe.liste_sommets[i] ) != T.end()   )
            {
                if( l[i] < l_min )
                {
                    l_min = l[i];
                    i_min = i;
                }
            }
          }

          /*
          cout << "\n" << T.size() << endl;
          cout << l_min << endl;
          cout << i_min << endl;
          */

          Point point_a_retirer = graphe.liste_sommets[i_min];

          //cout << point_a_retirer << endl;

          T.erase(remove(T.begin(), T.end(), point_a_retirer), T.end());

          S[i_min] = point_a_retirer;

          for(int j = 0 ; j<n ; ++j)
          {
              if( (c[i_min][j] != inf) && (  find(T.begin(),T.end(), graphe.liste_sommets[j] )  != T.end()  )  )
              {
                 if( l[j] > l[i_min] + c[i_min][j] )
                 {
                    l[j] = l[i_min] + c[i_min][j];
                    p[j] = graphe.liste_sommets[i_min];
                 }
              }
          }

    }

    for(int i=0;i<n;++i)
    {
        cout << l[i] << " ";
    }
    cout << "\n" <<endl;


    //on reconstruit le chemin du premier sommet au dernier sommet à partir de p


    Point depart_remonte = graphe.liste_sommets[n-1];
    vector<Point> points_chemin = {depart_remonte};
    vector<Point>::iterator it = find(S.begin(),S.end(),depart_remonte);
    int indice = distance(S.begin(), it);


    while (depart_remonte != graphe.liste_sommets[0])
    {
        depart_remonte = p[indice];
        points_chemin.push_back(depart_remonte);
        it = find(S.begin(),S.end(),depart_remonte);
        indice = distance(S.begin(), it);
    }

    vector<Point>::iterator its;

    for(its=points_chemin.begin();its!=points_chemin.end();++its)
    {
        cout << *its;
    }

    return( points_chemin  );

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



double distance_point_segment(const Point& A, const Segment& S)
{
    Segment P1A=Segment(S.P1,A);
    Segment P1P2=Segment(S.P1,S.P2);

    double P1H=produit_scalaire(P1A,P1P2)/(norme(P1P2));
    printf("P1H:%lf\n",P1H);
    double AH=sqrt(norme(P1A)*norme(P1A)-P1H*P1H);
    return(AH);
}


Obstacle transformation_padding(const Obstacle& Ob,double R)
{

    int nb_sommets=Ob.nbsom;
    const vector<Segment> segments_obst = Ob.segments_of_obstacle();
    const vector<Point> points_obs=Ob.sommets;
    vector<Point> sommets_coin(8*nb_sommets,Point());
    vector<Segment> S(nb_sommets,Segment());
    vector<Point> v=normales_ext(Ob);
    for(int i=0;i<nb_sommets;++i)
    {
        Point P0=Point(0,0);
        Point P1=Point(0,0);
        Segment S0=Segment(P0,P1);
        S[i]=segments_obst[i]+v[i]*R;
        //printf("S[%d]=((%lf,%lf)et(%lf,%lf))\n",i,S[i].P1.x,S[i].P1.y,S[i].P2.x,S[i].P2.y);
    }
    int nbsom=8*nb_sommets;
    Segment S1;
    Segment S2;
    Point P;
    double x;
    double y;
    double xa;
    double ya;
    double xb;
    double yb;
    Point B;
    Segment S3;
    Point P2;
    for(int j=0;j<nb_sommets;++j)
    {
        S1=segments_obst[j];
        S2=segments_obst[j+1];
        P2=S[j].P2;
        xa=points_obs[j].x;
        ya=points_obs[j].y;
        xb=xa+1;
        yb=ya;
        //printf("(xa,ya)=(%lf,%lf)\n",xa,ya);
        B=Point(xb,yb);
        S3=Segment(B,P2);
        double theta=acos(produit_scalaire(S1,S2)/(norme(S1)*norme(S2)));
        //double cos_theta_0=produit_scalaire(S3,S2)/(norme(S1)*norme(S3));
        double cos_theta_0=produit_scalaire(S3,S2)/(norme(S2)*norme(S3));
        double sin_theta_0=sqrt((1-(cos_theta_0)*(cos_theta_0)));
        //printf("j,theta,cos_theta_0,sin_theta_0=(%d,%lf,%lf,%lf)\n",j,theta,cos_theta_0,sin_theta_0);
        for(int k=0; k<8;++k)
        {
            x=Ob.sommets[j].x+R*cos(theta*k/8)*cos_theta_0;
            y=Ob.sommets[j].y+R*sin(theta*k/8)*sin_theta_0;

            P=Point(x,y);
            sommets[8*j+k]=P;
        }
    }
    Obstacle O=Obstacle(nbsom,sommets);
    //printf("Bonjour3\n");
    return(O);
}

