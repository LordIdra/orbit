#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Numbers.h"
#include "Fonts.h"

using std::vector;




enum alignment;


class TextHandler {

private:
    static GLuint vao;
    static GLuint vbo;
    
    static Shader shader;

    static vector<float> vertex_data;

    static float window_x;
    static float window_y;
    
    static afloat zoom_x;
    static afloat zoom_y;

    static afloat offset_x;
    static afloat offset_y;


public:
    static void Init();
    static void Render(std::string text, afloat in_x, afloat in_y, int align, float size, float r, float g, float b);

    static void UpdateScreenSize(int window_x, int window_y);
    static void UpdateZoom(afloat zoom);
    static void UpdateOffset(afloat offset_x, afloat offset_y);

    static void DrawText();
};