#include "SolarSystem.h"



// Function to translate orbital characteristics into vectors, and then
// use them to create a Planet object
Planet CreatePlanetFromOrbit(
        string            name,                   // name
        double            mass,                   // kg
        double            radius,                 // km
        double            perihelion,             // km
        double            perihelion_argument,    // degrees
        double            velocity,               // km/s
        float r, float g, float b, float a)       // 0-1
{
    // Calculate perihelion argument scalars
    double arg_x = 1;
    double arg_y = 0;

    // Calculate perihelion position in terms of X and Y
    double pos_x = double(double(perihelion) * arg_x);
    double pos_y = double(double(perihelion) * arg_y);

    // Calculate perihelion velocity in terms of X and Y
    // Invert argument X and Y as the velocity is perpendicular to position, relative to (0, 0)
    double vel_x = velocity * arg_y;
    double vel_y = velocity * arg_x;

    // Finally, create the planet object
    return Planet(name, mass, radius, pos_x, pos_y, vel_x, vel_y, r, g, b);
}





vector<Planet> GetPlanets()
{
    // Create a vector with every planet defined above
    vector<Planet> planets;


    // https://nssdc.gsfc.nasa.gov/planetary/factsheet/mercuryfact.html
    // https://en.wikipedia.org/wiki/Mercury_(planet)
    planets.push_back(CreatePlanetFromOrbit(
        string("Mercury"),               // Name
        0.33011  * pow(10, 24),          // Mass
        2439700,                         // Radius
        69.817   * pow(10, 9),           // Perihelion
        29.124,                          // Perihelion argument
        38860,                           // Max. orbital velocity
        0.86, 0.81, 0.79, 1.0));         // Color


    // https://nssdc.gsfc.nasa.gov/planetary/factsheet/venusfact.html
    // https://en.wikipedia.org/wiki/Venus
    planets.push_back(CreatePlanetFromOrbit(
        string("Venus"),                 // Name
        4.8675  * pow(10, 24),           // Mass
        6051800,                         // Radius
        107.476   * pow(10, 9),          // Perihelion
        54.884,                          // Perihelion argument
        35260,                           // Max. orbital velocity
        0.66, 0.35, 0.18, 1.0));         // Color
    return planets;
}





// Creates the sun as Star object with every planet as a child
Star GetSun()
{
    // Create the sun
    return Star(
        GetPlanets(),                             // Starting planets
        string("The Sun"),                        // Name
        double(1.989 * pow(10, 30)),              // Mass (the reason that double exists)
        double(695700000),                        // Radius
        double(0),                                // Position X
        double(0),                                // Position Y
        double(0),                                // Velocity X
        double(0),                                // Velocity Y
        1.0, 1.0, 0.0);                      // Color
}