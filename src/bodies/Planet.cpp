#include "Planet.h"




Planet::Planet(
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
    radius = starting_radius;
    r = s_r;
    g = s_g;
    b = s_b;
    a = s_a;
}



void Planet::Render()
{
    // Draw the planet itself
    GeometryHandler::DrawPolygon(pos_x.convert_to<float>(), pos_y.convert_to<float>(), 30, radius.convert_to<float>() * 1000, r, g, b, a);
  
    /*// Planet information
    // Name
    int width = FC_GetWidth(Fonts::ScifiMediumWhite, name);
    FC_Draw(Fonts::ScifiMediumWhite, renderer, (screen_x) + (screen_radius) + 65 - (width / 2), screen_y - 40, name);

    
    // Mass
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