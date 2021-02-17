#pragma once



class WindowInformation {
private:
    WindowInformation();

public:
    
    static float window_x;
    static float window_y;

    static double offset_x;
    static double offset_y;

    static double zoom_x;
    static double zoom_y;
    
    static double zoom;

    static void Update(float in_window_x, float in_window_y, double in_offset_x, double in_offset_y, double in_zoom);
};