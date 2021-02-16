#include "GeometryHandler.h"

#include <iostream>



GLuint GeometryHandler::vao = 0;
GLuint GeometryHandler::vbo = 0;
GLuint GeometryHandler::ebo = 0;

Shader GeometryHandler::shader = Shader();

vector<float> GeometryHandler::vertex_data = vector<float>();
vector<unsigned int> GeometryHandler::index_data = vector<unsigned int>();

int GeometryHandler::triangle_count = 0;
int GeometryHandler::index_counter = 0;

float GeometryHandler::window_x = 1;
float GeometryHandler::window_y = 1;

afloat GeometryHandler::zoom_x = 1;
afloat GeometryHandler::zoom_y = 1;

afloat GeometryHandler::offset_x = 1;
afloat GeometryHandler::offset_y = 1;




void GeometryHandler::Init() {
    // Generate shaders
    shader = Shader("shaders/TriangleVertex.glsl", "shaders/TriangleFragment.glsl");
    shader.Use();

    // Generate buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Bind bffers for more  initialization
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Vertex attibute handling
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Disable shaders
    glUseProgram(0);
}

void GeometryHandler::Render() {
    // Create transformation matrix
    glm::mat4 transform_matrix = glm::mat4(1.0f);
    transform_matrix = glm::translate(transform_matrix, glm::vec3((offset_x/zoom_x).convert_to<float>(), -(offset_y/zoom_y).convert_to<float>(), 0.0f));
    transform_matrix = glm::scale(transform_matrix, glm::vec3((1/zoom_x).convert_to<float>(), (1/zoom_y).convert_to<float>(), 1.0f));

    // Handle shader
    shader.Use();
    shader.SetMat4("transform_matrix", 1, glm::value_ptr(transform_matrix));

    // Bind vertex array object
    glBindVertexArray(vao);

    // Copy data in our vectors to the GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), &vertex_data[0], GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(unsigned int), &index_data[0], GL_DYNAMIC_DRAW);
    
    // Draw shapes
    glDrawElements(GL_TRIANGLES, triangle_count*3, GL_UNSIGNED_INT, 0);

    // Reset vectors and counters and whatnot
    vertex_data.clear();
    index_data.clear();

    index_counter = 0;
    triangle_count = 0;
}





void GeometryHandler::AddVertex(float x, float y, float r, float g, float b, float a) {
    vertex_data.push_back(x);
    vertex_data.push_back(-y);
    vertex_data.push_back(r);
    vertex_data.push_back(g);
    vertex_data.push_back(b);
    vertex_data.push_back(a);
}

void GeometryHandler::AddIndex(int index) {
    index_data.push_back(index);
}





void GeometryHandler::UpdateScreenSize(int x, int y) {
    window_x = x;
    window_y = y;
}

void GeometryHandler::UpdateZoom(afloat zoom) {
    zoom_x = window_x * zoom;
    zoom_y = window_y * zoom;
}

void GeometryHandler::UpdateOffset(afloat x, afloat y) {
    offset_x = x;
    offset_y = y;
}





void GeometryHandler::DrawTriangle(afloat in_x1, afloat in_y1, afloat in_x2, afloat in_y2, afloat in_x3, afloat in_y3, float r, float g, float b, float a) {
    // Convert input afloats to normal floats
    float x1 = in_x1.convert_to<float>();
    float y1 = in_y1.convert_to<float>();
    float x2 = in_x2.convert_to<float>();
    float y2 = in_y2.convert_to<float>();
    float x3 = in_x3.convert_to<float>();
    float y3 = in_y3.convert_to<float>();

    // Vertices
    AddVertex(x1, y1, r, g, b, a);
    AddVertex(x2, y2, r, g, b, a);
    AddVertex(x3, y3, r, g, b, a);

    // Indices
    AddIndex(index_counter);
    AddIndex(index_counter+1);
    AddIndex(index_counter+2);

    // Increment index counter (3 indices have been used) and triangle counter (1 triangle has been drawn)
    index_counter += 3;
    triangle_count += 1;
}

void GeometryHandler::DrawRectangle(afloat in_x1, afloat in_y1, afloat in_x2, afloat in_y2, float r, float g, float b, float a) {
    // Convert input afloats to normal floats
    float x1 = in_x1.convert_to<float>();
    float y1 = in_y1.convert_to<float>();
    float x2 = in_x2.convert_to<float>();
    float y2 = in_y2.convert_to<float>();

    // Vertices
    AddVertex(x1, y1, r, g, b, a);
    AddVertex(x1, y2, r, g, b, a);
    AddVertex(x2, y1, r, g, b, a);
    AddVertex(x2, y2, r, g, b, a);

    // Indices
    AddIndex(index_counter);
    AddIndex(index_counter+1);
    AddIndex(index_counter+2);
    AddIndex(index_counter+1);
    AddIndex(index_counter+2);
    AddIndex(index_counter+3);

    // Increment index counter (4 indices have been used) and triangle counter (2 triangles have been drawn)
    index_counter += 4;
    triangle_count += 2;
}

void GeometryHandler::DrawLine(afloat in_x1, afloat in_y1, afloat in_x2, afloat in_y2, float width, float r, float g, float b, float a) {
    // Convert input afloats to normal floats
    float x1 = in_x1.convert_to<float>();
    float y1 = in_y1.convert_to<float>();
    float x2 = in_x2.convert_to<float>();
    float y2 = in_y2.convert_to<float>();

    // Calculate gradient and perpendicular gradient
    float gradient = (y1 - y2) / (x1 - x2);
    float theta = (atan(gradient))-1.57;

    float add_x = cos(theta) * width;
    float add_y = sin(theta) * width;
    
    // Handle scaling
    width /= 100;

    // Vertices
    AddVertex(x1 - add_x, y1 - add_y, r, g, b, a);
    AddVertex(x1 + add_x, y1 + add_y, r, g, b, a);
    AddVertex(x2 - add_x, y2 - add_y, r, g, b, a);
    AddVertex(x2 + add_x, y2 + add_y, r, g, b, a);

    // Indices
    AddIndex(index_counter);
    AddIndex(index_counter+1);
    AddIndex(index_counter+2);
    AddIndex(index_counter+1);
    AddIndex(index_counter+2);
    AddIndex(index_counter+3);

    // Increment index counter (4 indices have been used) and triangle counter (2 triangles have been drawn)
    index_counter += 4;
    triangle_count += 2;
}

void GeometryHandler::DrawPolygon(afloat in_cx, afloat in_cy, float sides, float radius, float r, float g, float b, float a) {
    // All explained on this site
    /* http://slabode.exofire.net/circle_draw.shtml */

    // Convert input afloats to normal floats
    float cx = in_cx.convert_to<float>();
    float cy = in_cy.convert_to<float>();

    float theta = 2 * 3.1415926 / float(sides); 
	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);
	
	float x = radius; 
	float y = 0; 
    
	AddVertex(cx, cy, r, g, b, a);
    
	for(int ii = 0; ii < sides; ii++) 
	{ 
		AddVertex(x + cx, y + cy, r, g, b, a);

		float tx = -y; 
		float ty = x;  

		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 

		x *= radial_factor; 
		y *= radial_factor; 

        // just works. don't touch.
        AddIndex(index_counter);
        AddIndex(index_counter + ii);
        AddIndex(index_counter + ii + 1);

        if (ii == sides - 1) {
            AddIndex(index_counter);
            AddIndex(index_counter + ii + 1);
            AddIndex(index_counter + 1);
        }
	}

    // Increment index counter (sides+1 indices have been used) and triangle counter (sides triangles have been drawn)
    index_counter += sides + 1;
    triangle_count += sides + 1;
}