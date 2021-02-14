#include "SolarSystem.h"



// Function to translate orbital characteristics into vectors, and then
// use them to create a Planet object
Planet CreatePlanetFromOrbit(
        string            name,                   // name
        afloat            mass,                   // kg
        afloat            radius,                 // km
        afloat            perihelion,             // km
        afloat            perihelion_argument,    // degrees
        afloat            velocity,               // km/s
        float r, float g, float b, float a)       // 0-1
{
    // Calculate perihelion argument scalars
    afloat arg_x = 1;
    afloat arg_y = 0;

    // Calculate perihelion position in terms of X and Y
    afloat pos_x = afloat(afloat(perihelion) * arg_x);
    afloat pos_y = afloat(afloat(perihelion) * arg_y);

    // Calculate perihelion velocity in terms of X and Y
    // Invert argument X and Y as the velocity is perpendicular to position, relative to (0, 0)
    afloat vel_x = velocity * arg_y;
    afloat vel_y = velocity * arg_x;

    // Finally, create the planet object
    return Planet(name, mass, radius, pos_x, pos_y, vel_x, vel_y, r, g, b, a);
}





/*
 * =====[MERCURY]=====
 * https://nssdc.gsfc.nasa.gov/planetary/factsheet/mercuryfact.html
 * https://en.wikipedia.org/wiki/Mercury_(planet)
 */
Planet GetMercury()
{
    return CreatePlanetFromOrbit(
        string("Mercury"),                       // Name
        afloat(0.33011  * pow(10, 24)),          // Mass
        afloat(2439700),                         // Radius
        afloat(69.817   * pow(10, 9)),           // Perihelion
        afloat(29.124),                          // Perihelion argument
        afloat(38860),                           // Max. orbital velocity
        0.5, 0.5, 0.5, 1.0);           // Color
}



// Creates the sun as Star object with every planet as a child
Star GetSun()
{
    // Create a vector with every planet defined above
    vector<Planet> planets;

    planets.push_back(GetMercury());

    // Create the sun
    return Star(
        planets,                                  // Starting planets
        string("The Sun"),                        // Name
        afloat(1.989 * pow(10, 30)),              // Mass (the reason that afloat exists)
        afloat(695700000),                        // Radius
        afloat(0),                                // Position X
        afloat(0),                                // Position Y
        afloat(0),                                // Velocity X
        afloat(0),                                // Velocity Y
        1.0, 1.0, 0.0, 1.0);                      // Color
}