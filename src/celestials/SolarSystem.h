#pragma once

#include "Planet.h"
#include "Star.h"

#include <math.h>
#include <vector>

using std::vector;



Planet CreatePlanetFromOrbit(
        string            name,                   // name
        afloat            mass,                   // kg
        afloat            radius,                 // km
        afloat            perihelion,             // km
        afloat            perihelion_argument,    // degrees
        afloat            velocity,               // km/s
        SDL_Color color);


Planet  GetMercury();


vector<Planet>  GetPlanets();
Star            GetSun();