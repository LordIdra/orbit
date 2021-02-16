#pragma once

#include <vector>
#include <math.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Numbers.h"

using std::vector;




class GeometryHandler {

private:
    static GLuint vao;
    static GLuint vbo;
    static GLuint ebo;

    static Shader shader;

    static vector<float> vertex_data;
    static vector<unsigned int> index_data;

    static int triangle_count;
    static int index_counter;

    static float window_x;
    static float window_y;

    static afloat zoom_x;
    static afloat zoom_y;

    static afloat offset_x;
    static afloat offset_y;

    static void AddVertex(float x, float y, float r, float g, float b, float a);
    static void AddIndex(int index);

    GeometryHandler();


public:
    static void Init();
    static void Render();

    static void UpdateScreenSize(int window_x, int window_y);
    static void UpdateZoom(afloat zoom);
    static void UpdateOffset(afloat offset_x, afloat offset_y);

    static void DrawTriangle (afloat x1, afloat y1, afloat x2, afloat y2, afloat x3, afloat y3, float r, float g, float b, float a);
    static void DrawRectangle(afloat x1, afloat y1, afloat x2, afloat y2, float r, float g, float b, float a);
    static void DrawLine     (afloat x1, afloat y1, afloat x2, afloat y2, float width, float r, float g, float b, float a);
    static void DrawPolygon  (afloat x, afloat y, float sides, float radius, float r, float g, float b, float a);
};