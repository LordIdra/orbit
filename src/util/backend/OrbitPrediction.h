#pragma once

#include <vector>
#include <map>
#include <SDL2/SDL.h>

#include "Body.h"

using std::vector;
using std::map;





struct OrbitPoint {
    
    double pos_x;
    double pos_y;

    double vel_x;
    double vel_y;

    
    OrbitPoint(double pos_x, double pos_y, double vel_x, double vel_y);

    double Speed();
    double Distance(double parent_x, double parent_y);
    double Angle(double parent_x, double parent_y);
};


vector<vector<OrbitPoint>> PredictOrbits(int time_steps, int time_step_size, vector<Body> system);