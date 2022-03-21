#include "complex_hull.hpp"

int main () {
    complex_hull A;
    // Même objet que celui du rapport
    Point P1(2,4);
    Point P2(9,5);
    Point P3(9,9);
    Point P4(4,10);
    A+=P1;
    A+=P2;
    A+=P3;
    A+=P4;
    A.set_center(Point(6,8));
    cout << A;
    int e = idx_ref(A);
    cout << "La reference se trouve sur le cote "<<e << endl;
    cout << "Secteurs angulaire entre chaque rayon a partir de 0" << endl;
    vector<pair<double,double>> E(sector_mesh(A));
    double r1 = radius(A,160);
    // Libre à vous d'essayer d'autres valeurs
    //double r3 = radius(A,130.);
    //double r4 = radius(A,345);
    cout << "Rayon de l'objet pour theta de 160 = " << r1; 
    //cout << "R1 = "<<r1 << " R2 = " << r2<< " R3 = " << r3 << endl;
}