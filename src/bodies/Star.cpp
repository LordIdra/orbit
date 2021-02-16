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


void Star::Render(afloat zoom)
{
    // First, render all child planets
    for (Planet planet : planets) planet.Render(zoom);



    // Draw the star itself
    GeometryHandler::DrawPolygon(pos_x.convert_to<float>(), pos_y.convert_to<float>(), 30, radius.convert_to<float>(), r, g, b, a);


  
    // Star information
    // Calculate alpha values according to zoom level
    // TODO tomorrow

    // Screen position variables
    afloat info_name_x = pos_x + (radius * 2);
    afloat info_name_y = pos_y - (zoom * 70);

    afloat info_value_x = pos_x + (radius * 2) + (zoom * 200);
    afloat info_value_y = pos_y - (zoom * 70);

    // Background
    GeometryHandler::DrawRectangle(
        pos_x + (radius * 2), 
        pos_y - (zoom * 100), 
        pos_x + (radius * 2) + (zoom * 200), 
        pos_y + (zoom * 100), 
        0.0f, 0.0f, 0.0f, 0.6f);

    // Name
    TextHandler::DrawText(name, pos_x + (radius * 2) + (zoom * 100), pos_y - (zoom * 100), ALIGN_CENTRE, 0.6f, 1.0f, 1.0f, 1.0f, 1.0f);

    
    // Mass
    string mass_as_string = make_standard_mass(mass);

    TextHandler::DrawText("MASS", info_name_x, info_name_y, ALIGN_LEFT, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);
    TextHandler::DrawText(mass_as_string, info_value_x, info_value_y, ALIGN_RIGHT, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);


    // Radius
    string radius_as_string = make_standard_distance(radius);

    TextHandler::DrawText("RADIUS", info_name_x, info_name_y + (zoom*20), ALIGN_LEFT, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);
    TextHandler::DrawText(radius_as_string, info_value_x, info_value_y + (zoom*20), ALIGN_RIGHT, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);


    // Velocity
    string velocity_as_string = make_standard_velocity(GetVelocity());

    TextHandler::DrawText("VELOCITY", info_name_x, info_name_y + (zoom*40), ALIGN_LEFT, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);
    TextHandler::DrawText(velocity_as_string, info_value_x, info_value_y + (zoom*40), ALIGN_RIGHT, 0.35f, 1.0f, 1.0f, 1.0f, 1.0f);
}