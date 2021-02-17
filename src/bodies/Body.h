#pragma once

#include <math.h>
#include <string>

using std::string;




const double GRAVITATIONAL_CONSTANT = 0.000000000066742;


const double cutoff_threshold = double(0.0000000001);


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
    double mass;
    
    double pos_x;
    double pos_y;

    double vel_x;
    double vel_y;

    double influence_radius;



    
    Body(string starting_name, double starting_mass, double starting_pos_x, double starting_pos_y, double starting_vel_x, double starting_vel_y);

    double GetDistance(double x, double y);
    double GetVelocity();
    double GetKineticEnergy();

    void ApplyGravitationalForce(double magnitude, Body &body);
    void ApplyVelocity(double magnitude);
};