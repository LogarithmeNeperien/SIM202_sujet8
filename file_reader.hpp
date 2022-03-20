#ifndef file_reader_hpp
#define file_reader_hpp

#include "geometry.hpp"
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

vector<Obstacle> reading(char* nom_fichier);

#endif