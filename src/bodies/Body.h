#pragma once

#include <math.h>
#include <string.h>

#include "Numbers.h"

using std::string;




const afloat cutoff_threshold = afloat(0.0000000001);


class Body
{
public:
    // Still not sure if these should be public. They all need to be accessed
    // by external functions, and doing it like this is much cleaner, as opposed
    // to having about 8 various setter/getter functions, but making such
    // variables public is apparently considered bad practice?
    // https://softwareengineering.stackexchange.com/questions/143736/why-do-we-need-private-variables
    // https://softwareengineering.stackexchange.com/questions/21802/when-are-getters-and-setters-justified?noredirect=1&lq=1

    string name;
    afloat mass;
    
    afloat pos_x;
    afloat pos_y;

    afloat vel_x;
    afloat vel_y;

    afloat influence_radius;



    
    Body(string starting_name, afloat starting_mass, afloat starting_pos_x, afloat starting_pos_y, afloat starting_vel_x, afloat starting_vel_y);

    afloat GetDistance(afloat x, afloat y);
    afloat GetVelocity();
    afloat GetKineticEnergy();

    void ApplyGravitationalForce(afloat magnitude, Body &body);
    void ApplyVelocity(afloat magnitude);
};