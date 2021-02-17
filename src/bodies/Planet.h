#pragma once

#include <SDL2/SDL.h>

#include "Unit.h"
#include "Text.h"
#include "Geometry.h"
#include "Fonts.h"
#include "Body.h"





class Planet : public Body
{
public:
    float r;
    float g;
    float b;
    float a;

    float info_a;
    float path_a;
    
    double        radius;


    Planet(
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