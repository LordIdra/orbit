#pragma once

#include <vector>
#include <math.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "WindowInformation.h"

using std::vector;




class Geometry {

private:
    static GLuint vao;
    static GLuint vbo;
    static GLuint ebo;

    static Shader shader;

    static vector<float> vertex_data;
    static vector<unsigned int> index_data;

    static int triangle_count;
    static int index_counter;

    static void AddVertex(float x, float y, float r, float g, float b, float a);
    static void AddIndex(int index);

    Geometry();


public:
    static void Init();
    static void Render();

    static void DrawTriangle (double x1, double y1, double x2, double y2, double x3, double y3, float r, float g, float b, float a);
    static void DrawRectangle(double x1, double y1, double x2, double y2, float r, float g, float b, float a);
    static void DrawLine     (double x1, double y1, double x2, double y2, float width, float r, float g, float b, float a);
    static void DrawPolygon  (double x, double y, float sides, float radius, float r, float g, float b, float a);
};