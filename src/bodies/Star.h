#pragma once

#include <vector>

#include "Unit.h"
#include "Planet.h"

using std::vector;




class Star : public Body
{
public:
    float r;
    float g;
    float b;
    float a;
    
    float info_a;

    double          radius;
    vector<Planet>  planets;


    Star(
        vector<Planet> starting_planets,
        string starting_name,
        double starting_mass,
        double starting_radius,
        double starting_pos_x, 
        double starting_pos_y,
        double starting_vel_x,
        double starting_vel_y,
        float s_r, float s_b, float s_g);

    void Render(double zoom, float window_x);
};