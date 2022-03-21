#include "padding.hpp"

Obstacle transformation_padding(const Obstacle& Ob,double R)
{

    int nb_sommets=Ob.nbsom;
    const vector<Segment> segments_obst = Ob.segments_of_obstacle();
    const vector<Point> points_obs=Ob.sommets;
    vector<Point> sommets_coin;
    vector<Point> v=normales_ext(Ob);

    Segment seg_g;
    Segment seg_d;

    Segment normale_g;
    Segment normale_d;

    double theta = 0;
    int nonconvexe=0;
    double a_d,a_g,b_d,b_g,x_intersection,y_intersection;
    Point inter;

    for(int j=0; j<nb_sommets; ++j)
    { 
        if(j==0){
            normale_g = Segment(points_obs[0],points_obs[0] + v[0]*R);

            normale_d = Segment(points_obs[0],points_obs[0] + v[nb_sommets-1]*R);
            seg_g=Segment(normale_g.P2,points_obs[1]+v[0]*R);
            seg_d=Segment(normale_d.P2,points_obs[nb_sommets-1]+v[nb_sommets-1]*R);
            //normale_d et normale_g sont de normes R
            theta=acos(produit_scalaire(normale_d,normale_g) / (R*R) );

        }else if(j==nb_sommets-1){

            normale_g = Segment(points_obs[nb_sommets-1],points_obs[nb_sommets-1] + v[nb_sommets-1]*R);
            normale_d = Segment(points_obs[nb_sommets-1],points_obs[nb_sommets-1] + v[nb_sommets-2]*R);
            seg_g=Segment(normale_g.P2,points_obs[0]+v[nb_sommets-1]*R);
            seg_d=Segment(normale_d.P2,points_obs[nb_sommets-2]+v[nb_sommets-2]*R);
            //normale_d et normale_g sont de normes R
            theta=acos(produit_scalaire(normale_d,normale_g) / (R*R) );

        }else {
            normale_g = Segment(points_obs[j],points_obs[j] + v[j]*R);
            normale_d = Segment(points_obs[j],points_obs[j] + v[j-1]*R);
            seg_g=Segment(normale_g.P2,points_obs[j+1]+v[j]*R);
            seg_d=Segment(normale_d.P2,points_obs[j-1]+v[j-1]*R);
            //normale_d et normale_g sont de normes R
            theta=acos(produit_scalaire(normale_d,normale_g) / (R*R) );


        }
        
        if(intersection_segment(seg_g,seg_d,0.01,0.01))
        {
            nonconvexe+=1;
            if(seg_d.P1.x==seg_d.P2.x)
            {
                a_g=(seg_g.P2.y-seg_g.P1.y)/(seg_g.P2.x-seg_g.P1.x); //si seg_d est verticale seg_g ne pas être verticale
                b_g=seg_g.P2.y-a_g*seg_g.P2.x;
                x_intersection=seg_d.P1.x;
                y_intersection=a_g*x_intersection+b_g;
            }else if(seg_g.P1.x==seg_g.P2.x){
                a_d=(seg_d.P2.y-seg_d.P1.y)/(seg_d.P2.x-seg_d.P1.x); //si seg_g est verticale seg_d ne pas être verticale
                b_d=seg_d.P2.y-a_d*seg_d.P2.x;
                x_intersection=seg_g.P1.x;
                y_intersection=a_d*x_intersection+b_d;
            }else{
                a_d=(seg_d.P2.y-seg_d.P1.y)/(seg_d.P2.x-seg_d.P1.x);
                b_d=seg_d.P2.y-a_d*seg_d.P2.x;
                a_g=(seg_g.P2.y-seg_g.P1.y)/(seg_g.P2.x-seg_g.P1.x);
                b_g=seg_g.P2.y-a_g*seg_g.P2.x;
                x_intersection=(b_g-b_d)/(a_d-a_g);
                y_intersection=a_d*x_intersection+b_d;
            }
            inter=Point(x_intersection,y_intersection);
            sommets_coin.push_back(inter);

        }else{ 
            sommets_coin.push_back(normale_d.P2);
            for(int k=1;k<7;++k)
            {
                Segment normale_normale_d = normale_point(normale_d,normale_d.P2);

                Point vect = normale_normale_d.P2 - normale_normale_d.P1;

                vect = vect * (1/norme(vect));

                normale_normale_d.P2 = normale_normale_d.P1 + vect;

                Point normale_d_unit = (normale_d.P2 - normale_d.P1) * (1 / norme(normale_d.P2 - normale_d.P1));
                Point angle = (normale_d_unit) * (R*cos(theta/7)) + (vect) * (R*sin(theta/7)) ;

                Point angle_final = angle + points_obs[j];

                sommets_coin.push_back(angle_final);

                normale_d = Segment(points_obs[j],angle_final);
            }
                sommets_coin.push_back(normale_g.P2);
        }
    }
    Obstacle obs_padding = Obstacle(8*(nb_sommets-nonconvexe)+nonconvexe,sommets_coin);

    return(obs_padding);
}

vector<Obstacle> vector_obs_padding(const vector<Obstacle>& Obs,double R){
    vector<Obstacle> vec_obs_padd;
    for (auto it = Obs.begin(); it != Obs.end();it++){
        vec_obs_padd.push_back(transformation_padding(*it,R));
    }
    return vec_obs_padd;
}