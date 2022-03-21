#include "graph.hpp"
#include <limits>
#include <algorithm>

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
        //on regarde si le segment prolong� a tap� un agnle
        if( intersection_segment(seg_milieu,segments_obst[i],0.1,0)  && !(point_segment(seg_milieu,segments_obst[i].P2,0)) )
        {
            comptage_intersect++;
        }
    }
    return comptage_intersect;

}

//renvoie true si le segment est valide par rapport � l'obstacle pass� en param�tre
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


          Point point_a_retirer = graphe.liste_sommets[i_min];

        cout << point_a_retirer << endl;

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


    //on reconstruit le chemin du premier sommet au dernier sommet � partir de p


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
