#include "Planet.h"




Planet::Planet(
        string starting_name,
        double starting_mass,
        double starting_radius,
        double starting_pos_x, 
        double starting_pos_y,
        double starting_vel_x,
        double starting_vel_y,
        float s_r, float s_g, float s_b)

        : Body(starting_name, starting_mass, starting_pos_x, starting_pos_y, starting_vel_x, starting_vel_y)
{
    radius = starting_radius;
    r = s_r;
    g = s_g;
    b = s_b;
    a = 1.0f;
    info_a = 0.0f;
    path_a = 0.0f;
}



void Planet::Render(double zoom, float window_x)
{
    // Draw the planet itself
    Geometry::DrawPolygon(pos_x, pos_y, 30, radius, r, g, b, a);
  
    // Planet information
    // Calculate various alpha values according to zoom level and radius
    float min_zoom = radius / (0.1 * window_x); // Zoom level at which the planet covers 10% of the screen
    float max_zoom = 100000000;
    float zoom_speed = 0.1f;

    // Information alpha
    if ((zoom < min_zoom) && (info_a > 0.0f)) info_a -= zoom_speed;
    if ((zoom > min_zoom) && (info_a < 1.0f) && (zoom < max_zoom)) info_a += zoom_speed;
    if ((zoom > max_zoom) && (info_a > 0.0f)) info_a -= zoom_speed;

    // Path alpha
    if ((zoom < min_zoom) && (info_a > 0.0f)) path_a -= zoom_speed;
    if ((zoom > min_zoom) && (info_a < 1.0f)) path_a += zoom_speed;


    // Screen position variables
    double info_name_x = pos_x + (radius * 2);
    double info_name_y = pos_y - (zoom * 70);

    double info_value_x = pos_x + (radius * 2) + (zoom * 200);
    double info_value_y = pos_y - (zoom * 70);


    // Background
    Geometry::DrawRectangle(
        pos_x + (radius * 2), 
        pos_y - (zoom * 100), 
        pos_x + (radius * 2) + (zoom * 200),
        pos_y + (zoom * 100), 
        0.0f, 0.0f, 0.0f, info_a / 1.67f);


    // Name
    Text::DrawText(name, pos_x + (radius * 2) + (zoom * 100), pos_y - (zoom * 100), ALIGN_CENTRE, 0.6f, 1.0f, 1.0f, 1.0f, info_a);

    
    // Mass
    string mass_as_string = Unit::MakeStandardMass(mass);

    Text::DrawText("MASS", info_name_x, info_name_y, ALIGN_LEFT, 0.35f, 1.0f, 1.0f, 1.0f, info_a);
    Text::DrawText(mass_as_string, info_value_x, info_value_y, ALIGN_RIGHT, 0.35f, 1.0f, 1.0f, 1.0f, info_a);


    // Radius
    string radius_as_string = Unit::MakeStandardDistance(radius);

    Text::DrawText("RADIUS", info_name_x, info_name_y + (zoom*20), ALIGN_LEFT, 0.35f, 1.0f, 1.0f, 1.0f, info_a);
    Text::DrawText(radius_as_string, info_value_x, info_value_y + (zoom*20), ALIGN_RIGHT, 0.35f, 1.0f, 1.0f, 1.0f, info_a);


    // Velocity
    string velocity_as_string = Unit::MakeStandardVelocity(GetVelocity());

    Text::DrawText("VELOCITY", info_name_x, info_name_y + (zoom*40), ALIGN_LEFT, 0.35f, 1.0f, 1.0f, 1.0f, info_a);
    Text::DrawText(velocity_as_string, info_value_x, info_value_y + (zoom*40), ALIGN_RIGHT, 0.35f, 1.0f, 1.0f, 1.0f, info_a);
}