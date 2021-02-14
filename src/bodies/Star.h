#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "TextHandler.h"
#include "GeometryHandler.h"
#include "Planet.h"

using std::vector;


class Star : public Body
{
public:
    float r;
    float g;
    float b;
    float a;

    afloat          radius;
    vector<Planet>  planets;
    vector<Body>    planets_as_bodies;


    Star(
        vector<Planet> starting_planets,
        string starting_name,
        afloat starting_mass,
        afloat starting_radius,
        afloat starting_pos_x, 
        afloat starting_pos_y,
        afloat starting_vel_x,
        afloat starting_vel_y,
        float s_r, float s_b, float s_g, float s_a);

    void Render();
};