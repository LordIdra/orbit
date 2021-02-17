#include "body.h"




// Initializer
Body::Body(string starting_name, double starting_mass, double starting_pos_x, double starting_pos_y, double starting_vel_x, double starting_vel_y) 
        : name(starting_name),
          mass(starting_mass),
          pos_x(starting_pos_x),
          pos_y(starting_pos_y),
          vel_x(starting_vel_x),
          vel_y(starting_vel_y)
{
    // Calculate cutoff point
    bool cutoff_found = false;
    double distance = 0;

    while (!cutoff_found) {
        if ((GRAVITATIONAL_CONSTANT * mass) / pow(distance, 3) < cutoff_threshold) {
            influence_radius = distance;
            cutoff_found = true;
        }

        distance += 100000;
    }
}


// Get distance of the Body from a specific point
double Body::GetDistance(double target_x, double target_y)
{
    return double(sqrt(pow(target_x - pos_x, 2) + pow(target_y - pos_y, 2)));
}

// Get velocity in km/s (not as a vector)
double Body::GetVelocity()
{
    return sqrt(pow(vel_x, 2) + pow(vel_y, 2));
}

// Get kinetic energy in KJ
double Body::GetKineticEnergy()
{
    return double((double(mass) * pow(GetVelocity(), 2)) / 2);
}



// Apply gravity to velocity vector
void Body::ApplyGravitationalForce(double magnitude, Body &body)
{
    // Applies gravity to the planet's velocity vector

    // Cowell orbital perturbation - simple and inaccurate, but gets the
    // job done. No need for optimisation, either, until we're handling large
    // numbers of objects
    // https://en.wikipedia.org/wiki/Perturbation_(astronomy)
    double acceleration = 
        (GRAVITATIONAL_CONSTANT
        * body.mass)
        / pow(GetDistance(body.pos_x, body.pos_y), 3);

    vel_x += (body.pos_x - pos_x) * acceleration * magnitude;
    vel_y += (body.pos_y - pos_y) * acceleration * magnitude;
}


// Apply velocity to position vector
void Body::ApplyVelocity(double magnitude)
{
    // Adds the velocity vector to the position vector
    // Magnitude specifies the time step
    pos_x += vel_x * magnitude;
    pos_y += vel_y * magnitude;
}