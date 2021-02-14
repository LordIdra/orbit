#pragma once

#include <vector>
#include <map>

#include "Body.h"

using std::vector;
using std::map;





struct OrbitPoint {
    
    afloat pos_x;
    afloat pos_y;

    afloat vel_x;
    afloat vel_y;

    
    OrbitPoint(afloat pos_x, afloat pos_y, afloat vel_x, afloat vel_y);

    afloat Speed();
    afloat Distance(afloat parent_x, afloat parent_y);
    afloat Angle(afloat parent_x, afloat parent_y);
};


vector<vector<OrbitPoint>> PredictOrbits(int time_steps, int time_step_size, vector<Body> system);