#include "body.h"




// Initializer
Body::Body(string starting_name, afloat starting_mass, afloat starting_pos_x, afloat starting_pos_y, afloat starting_vel_x, afloat starting_vel_y) 
        : name(starting_name),
          mass(starting_mass),
          pos_x(starting_pos_x),
          pos_y(starting_pos_y),
          vel_x(starting_vel_x),
          vel_y(starting_vel_y)
{
    // Calculate cutoff point
    bool cutoff_found = false;
    afloat distance = 0;

    while (!cutoff_found) {
        if ((GRAVITATIONAL_CONSTANT * mass) / power(distance, 3) < cutoff_threshold) {
            influence_radius = distance;
            cutoff_found = true;
        }

        distance += 100000;
    }

    std::cout << distance << "\n";
}


// Get distance of the Body from a specific point
afloat Body::GetDistance(afloat target_x, afloat target_y)
{
    return afloat(root(power(target_x - pos_x, 2) + power(target_y - pos_y, 2)));
}

// Get velocity in km/s (not as a vector)
afloat Body::GetVelocity()
{
    return root(power(vel_x, 2) + power(vel_y, 2));
}

// Get kinetic energy in KJ
afloat Body::GetKineticEnergy()
{
    return afloat((afloat(mass) * power(GetVelocity(), 2)) / 2);
}



// Apply gravity to velocity vector
void Body::ApplyGravitationalForce(afloat magnitude, Body &body)
{
    // Applies gravity to the planet's velocity vector

    // Cowell orbital perturbation - simple and inaccurate, but gets the
    // job done. No need for optimisation, either, until we're handling large
    // numbers of objects
    // https://en.wikipedia.org/wiki/Perturbation_(astronomy)
    afloat acceleration = 
        (GRAVITATIONAL_CONSTANT
        * body.mass)
        / power(GetDistance(body.pos_x, body.pos_y), 3);

    vel_x += (body.pos_x - pos_x) * acceleration * magnitude;
    vel_y += (body.pos_y - pos_y) * acceleration * magnitude;
}


// Apply velocity to position vector
void Body::ApplyVelocity(afloat magnitude)
{
    // Adds the velocity vector to the position vector
    // Magnitude specifies the time step
    pos_x += vel_x * magnitude;
    pos_y += vel_y * magnitude;
}