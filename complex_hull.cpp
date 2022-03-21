#include "complex_hull.hpp"

ostream& operator<<(ostream& os, const complex_hull& CH) {
    os << static_cast<Obstacle>(CH);
    os << "Centre = " << CH.center << endl;
    return os;
}

vector<Segment> radii(const complex_hull& CH){
    vector<Segment> radii;
    for (int i = 0; i < CH.nbsom; i++){
        Segment radius(CH.center,CH.sommets[i]);
        radii.push_back(radius);
    }
    return radii;
}


vector<double> sector_length(const complex_hull& CH){
    vector<double> sector_length;
    vector<Segment> radiuses = radii(CH);
    for (int i = 0; i < (CH.nbsom)-1; i++){
        sector_length.push_back(arclength(radiuses[i],radiuses[i+1]));
    }
    sector_length.push_back(arclength(radiuses[CH.nbsom-1],radiuses[0]));
    return sector_length;
}

int idx_ref(const complex_hull& CH){
    Segment ref(0,1);
    vector<Segment> radiuses(radii(CH));
    for (int i = 0; i < CH.nbsom-1; i++){
        if ( (produit_vectoriel(radiuses[i],ref)*produit_vectoriel(radiuses[i+1],ref) <= 0 ) ) return i;
    }
    return (CH.nbsom)-1;
}


vector<pair<double,double>> sector_mesh(const complex_hull& CH){
    
    vector<double> list_of_angles(sector_length(CH));
    vector<pair<double,double>> sec_mesh;
    Segment ref_angle(0,1);
    Segment ref_edge;
    
    int ref = idx_ref(CH);
    
    if (ref != CH.nbsom){
        ref_edge = Segment(CH.sommets[ref],CH.sommets[ref+1]);
    } else {
        ref_edge = Segment(CH.sommets[CH.nbsom-1],CH.sommets[0]);
    }
    Point p(CH.sommets[(ref+1) % CH.nbsom]);
    double start_angle = arclength(ref_angle,Segment(CH.center,p));
    for (int i = 0; i < CH.nbsom; i++){
        if (i == 0) {sec_mesh.push_back(make_pair(0.,start_angle));}
         else {
             sec_mesh.push_back(make_pair(sec_mesh[i-1].second,sec_mesh[i-1].second+list_of_angles[(i+ref)%CH.nbsom]));
             
             }
        cout << sec_mesh[i].first << "-" << sec_mesh[i].second << endl;
    }
    sec_mesh.push_back(make_pair(sec_mesh[CH.nbsom-1].second,sec_mesh[CH.nbsom-1].second+list_of_angles[ref]-start_angle));
    cout << sec_mesh[CH.nbsom].first << "-" << sec_mesh[CH.nbsom].second << endl;
    return sec_mesh;
}

int is_in(double x,const vector<pair<double,double>>& mesh){
    for (int i = 0; i < mesh.size();i++){
        if ((x >= mesh[i].first) and (x <= mesh[i].second)) return i;
    }
    return mesh.size();
}

// find which edge is concerned with the given angle
int which_edge(const complex_hull& CH,double angle){
    int ref = idx_ref(CH);
    vector<pair<double,double>> E(sector_mesh(CH));
    // indexation locale
    int pos = is_in(angle,E);
    // indexation globale
    return (pos+ref)%CH.nbsom;
}

double radius(const complex_hull& CH, double angle){
    vector<pair<double,double>> sec_mesh(sector_mesh(CH));
    int ref = is_in(angle,sec_mesh);
    double local_angle = angle-sec_mesh[ref].first;
    if (ref == 0) local_angle += (360-sec_mesh[CH.nbsom].first);

    int edge = which_edge(CH,angle);
    Point A(CH.sommets[edge]);
    Point B(CH.sommets[(edge+1)%CH.nbsom]);
    Segment AB(Segment(A,B));
    double nAB = norme(AB);
    Segment Pro(projection(CH.center,AB));
    Point P(Pro.P2);
    Segment OP(CH.center,P);
    double nOP = norme(OP);
    double alpha = arclength(Segment(CH.center,A),OP);
    double theta = alpha-local_angle;
    double radius = nOP/cos(theta*3.14159265/180);
    return radius;
}