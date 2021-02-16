#define _WIN32_WINNT 0x0601
#define SDL_MAIN_HANDLED

#include <iostream>
#include <vector>
#include <chrono>

#include <windows.h>

#include "Shader.h"
#include "TextHandler.h"
#include "GeometryHandler.h"

#include "SolarSystem.h"
#include "OrbitPrediction.h"



using std::vector;



/* https://www.pluralsight.com/blog/software-development/how-to-measure-execution-time-intervals-in-c-- */
/* https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html */
/* https://gist.github.com/sherjilozair/ac2ac5e3002b6f3becaef214ebe3cd7a */


afloat zoom = 500000000;

afloat mouse_x = 0;
afloat mouse_y = 0;

afloat mouse_x_previous = 0;
afloat mouse_y_previous = 0;

int window_x = 0;
int window_y = 0;

afloat offset_x = 0;
afloat offset_y = 0;

bool is_running = true;
bool mouse_down = false;

int step = 100000;

SDL_Event event;




void handle_input() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            // Quit
            is_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                // Quit
                is_running = false;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) mouse_down = true;  // Left mouse button down
            break;
        
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) mouse_down = false; // Left mouse button up
            break;
        
        case SDL_MOUSEWHEEL:
            // Zoom in/out
            afloat old_zoom = zoom;
            zoom *= 1 - (event.wheel.y*0.1);
            offset_x -= (mouse_x - (window_x/2)) * (old_zoom - zoom) * 2;
            offset_y -= (mouse_y - (window_y/2)) * (old_zoom - zoom) * 2;
            break;
        }
    }
}


int main(int argv, char** args)
{
    // Pre-window initialization
    Star sun = GetSun();

    SetProcessDPIAware();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,16);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);



    // Window creation
    SDL_Window *window = SDL_CreateWindow("Orbit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 10000, 10000, 
        SDL_WINDOW_ALLOW_HIGHDPI| SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GLContext context = SDL_GL_CreateContext(window);


    // Post-window initialization
    SDL_GetWindowSize(window, &window_x, &window_y);

    int mouse_cache_x;
    int mouse_cache_y;

    SDL_GetMouseState(&mouse_cache_x, &mouse_cache_y);

    mouse_x = mouse_cache_x;
    mouse_y = mouse_cache_y;

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    SDL_GL_SetSwapInterval(1);

    // Enable multisampling
    glViewport(0, 0, window_x, window_y);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Load fonts
    Fonts::InitializeFonts();

    GeometryHandler::Init();
    TextHandler::Init();


    // Mainloop
    while (is_running)
    {
        // Handle events
        handle_input();


        // Handle mouse
        int mouse_cache_x;
        int mouse_cache_y;

        SDL_GetMouseState(&mouse_cache_x, &mouse_cache_y);

        mouse_x = mouse_cache_x;
        mouse_y = mouse_cache_y;

        if (mouse_down) {
            offset_x -= (mouse_x_previous - mouse_x) * zoom * 2;
            offset_y -= (mouse_y_previous - mouse_y) * zoom * 2;
        }

        mouse_x_previous = mouse_x;
        mouse_y_previous = mouse_y;


        // Update dimension variables
        SDL_GetWindowSize(window, &window_x, &window_y);

        GeometryHandler::UpdateScreenSize(window_x, window_y);
        GeometryHandler::UpdateZoom(zoom);
        GeometryHandler::UpdateOffset(offset_x, offset_y);

        TextHandler::UpdateScreenSize(window_x, window_y);
        TextHandler::UpdateZoom(zoom);
        TextHandler::UpdateOffset(offset_x, offset_y);


        // Create a vector of all the bodies
        vector<Body> system_bodies;
        system_bodies.push_back(sun);
        
        for (Body planet : sun.planets) {
            system_bodies.push_back(planet);
        }


        // Simulate orbits
        vector<vector<OrbitPoint>> orbit_points = PredictOrbits(100, step, system_bodies);
        

        // Clear screen
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);


        // Draw paths
        for (vector<OrbitPoint> orbit_point_vector : orbit_points) {
            for (int i = 0; i < orbit_point_vector.size()-1; i++) {
                
                OrbitPoint orbit_point_1 = orbit_point_vector[i];
                OrbitPoint orbit_point_2 = orbit_point_vector[i+1];

                GeometryHandler::DrawLine(
                    orbit_point_1.pos_x.convert_to<float>(),
                    orbit_point_1.pos_y.convert_to<float>(),
                    orbit_point_2.pos_x.convert_to<float>(),
                    orbit_point_2.pos_y.convert_to<float>(),
                    zoom.convert_to<float>(), 1.0, 1.0, 1.0, 0.6);
            }
        }


        // Draw bodies
        sun.Render(zoom);


        // Update window
        GeometryHandler::Render();
        TextHandler::Render();

        SDL_GL_SwapWindow(window);
    }

    // Clean up
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);

    // Indicate successful execution
    return 0;
}