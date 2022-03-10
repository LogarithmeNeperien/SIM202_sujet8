#include <iostream>
#include "classe.hpp"
#include <vector>
using namespace std ;

int main()
{   
	char* nom_fichier = (char*)"obs3.txt";
	const vector<Obstacle> vect_obst = reading(nom_fichier);
    const Obstacle ob1 = vect_obst[0];
    cout << ob1 << endl;
	double rr=0.1;
    Obstacle OO=transformation_padding(ob1,rr);
    cout<<OO<<endl;
    return 0;
}
