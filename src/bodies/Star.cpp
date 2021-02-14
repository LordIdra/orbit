#include "Star.h"

Star::Star(
        vector<Planet> starting_planets,
        string starting_name,
        afloat starting_mass,
        afloat starting_radius,
        afloat starting_pos_x, 
        afloat starting_pos_y,
        afloat starting_vel_x,
        afloat starting_vel_y,
        float s_r, float s_g, float s_b, float s_a)

        : Body(starting_name, starting_mass, starting_pos_x, starting_pos_y, starting_vel_x, starting_vel_y)
{
    planets = starting_planets;
    radius = starting_radius;
    r = s_r;
    g = s_g;
    b = s_b;
    a = s_a;

    for (Planet planet : planets) {
        planets_as_bodies.push_back(Body(planet));
    }
}


void Star::Render()
{
    // First, render all child planets
    for (Planet planet : planets) planet.Render();

    // Draw the star itself
    GeometryHandler::DrawPolygon(pos_x.convert_to<float>(), pos_y.convert_to<float>(), 30, radius.convert_to<float>(), r, g, b, a);


    // Sphere of influence
    //aaFilledEllipseRGBA(renderer, screen_x, screen_y, int(influence_radius/zoom)*10, int(influence_radius/zoom)*10, color.r, color.g, color.b, 50);

  
    // Star information
    // Name 
    TextHandler::Render(name, pos_x + (radius * 3), pos_y - (radius * 1), 0.5f, 1.0f, 1.0f, 1.0f);

    
    /*// Mass
    string mass_as_string = make_standard_mass(mass);
    width = FC_GetWidth(Fonts::ScifiSmallWhite, mass_as_string);

    FC_Draw(Fonts::ScifiSmallWhite, renderer, (screen_x) + (screen_radius) + 10, screen_y - 20, "MASS");
    FC_Draw(Fonts::ScifiSmallWhite, renderer, (screen_x) + (screen_radius) + 120 - (width), screen_y - 20, mass_as_string);


    // Radius
    string radius_as_string = make_standard_distance(radius);
    width = FC_GetWidth(Fonts::ScifiSmallWhite, radius_as_string);

    FC_Draw(Fonts::ScifiSmallWhite, renderer, (screen_x) + (screen_radius) + 10, screen_y - 10, "RADIUS");
    FC_Draw(Fonts::ScifiSmallWhite, renderer, (screen_x) + (screen_radius) + 120 - (width), screen_y - 10, radius_as_string);


    // Velocity
    string velocity_as_string = make_standard_velocity(GetVelocity());
    width = FC_GetWidth(Fonts::ScifiSmallWhite, velocity_as_string);

    FC_Draw(Fonts::ScifiSmallWhite, renderer, (screen_x) + (screen_radius) + 10, screen_y, "VELOCITY");
    FC_Draw(Fonts::ScifiSmallWhite, renderer, (screen_x) + (screen_radius) + 120 - (width), screen_y, velocity_as_string);*/
}