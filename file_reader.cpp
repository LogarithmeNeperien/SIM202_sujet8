#include "file_reader.hpp"


vector<Obstacle> reading(char* nom_fichier){

	vector<Obstacle> list_obstacles;
	Obstacle ob(0,{});
	ifstream infile(nom_fichier);

	string line;

	// Balise rencontrées dans le fichier texte
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
	return list_obstacles;
}