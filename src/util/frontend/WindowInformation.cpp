#include "WindowInformation.h"



float WindowInformation::window_x = 1;
float WindowInformation::window_y = 1;

double WindowInformation::offset_x = 0;
double WindowInformation::offset_y = 0;

double WindowInformation::zoom_x = 0;
double WindowInformation::zoom_y = 0;

double WindowInformation::zoom = 1;


void WindowInformation::Update(float in_window_x, float in_window_y, double in_offset_x, double in_offset_y, double in_zoom) {
    
    window_x = in_window_x;
    window_y = in_window_y;

    offset_x = in_offset_x;
    offset_y = in_offset_y;

    zoom_x = in_window_x * in_zoom;
    zoom_y = in_window_y * in_zoom;

    zoom = in_zoom;
}