#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "WindowInformation.h"
#include "Shader.h"
#include "Fonts.h"

using std::vector;




enum alignment {
    ALIGN_LEFT = 0,
    ALIGN_CENTRE = 1,
    ALIGN_RIGHT = 2
};


struct TextObject {
    string text;
    float x;
    float y;
    float size;
    float r;
    float g;
    float b;
    float a;
};


class Text {

private:
    static GLuint vao;
    static GLuint vbo;
    
    static Shader shader;

    static vector<float> vertex_data;
    static vector<TextObject> text_objects;


public:
    static void Init();

    static void DrawText(std::string text, double in_x, double in_y, int align, float size, float r, float g, float b, float a);
    static void Render();
};