#ifndef padding_hpp
#define padding_hpp

#include "geometry.hpp"
#include "advanced_tools.hpp"

Obstacle transformation_padding(const Obstacle& Ob,double R);

vector<Obstacle> vector_obs_padding(const vector<Obstacle>& Obs,double R);
#endif
