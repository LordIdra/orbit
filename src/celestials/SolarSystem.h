#pragma once

#include "Planet.h"
#include "Star.h"

#include <math.h>
#include <vector>

using std::vector;



Planet CreatePlanetFromOrbit(
        string            name,                   // name
        double            mass,                   // kg
        double            radius,                 // km
        double            perihelion,             // km
        double            perihelion_argument,    // degrees
        double            velocity,               // km/s
        SDL_Color color);


Planet  GetMercury();


vector<Planet>  GetPlanets();
Star            GetSun();