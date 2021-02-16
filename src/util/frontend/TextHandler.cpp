#include "TextHandler.h"




GLuint TextHandler::vao = 0;
GLuint TextHandler::vbo = 0;

Shader TextHandler::shader = Shader();

vector<float> TextHandler::vertex_data = vector<float>();

float TextHandler::window_x = 1;
float TextHandler::window_y = 1;

afloat TextHandler::zoom_x = 1;
afloat TextHandler::zoom_y = 1;

afloat TextHandler::offset_x = 1;
afloat TextHandler::offset_y = 1;

vector<TextObject> TextHandler::text_objects = vector<TextObject>();




void TextHandler::Init() {
    // Generate shaders
    shader = Shader("shaders/TextVertex.glsl", "shaders/TextFragment.glsl");
    shader.Use();

    // Generate buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind buffers and allocate memory to VBO
    // ALWAYS make sure vbo has enough memory, just spent 3 hours
    // tracking down a bug caused by that
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    // Vertex attibute handling
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Unbind vertex array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}





void TextHandler::UpdateScreenSize(int x, int y) {
    window_x = x;
    window_y = y;

    Fonts::UpdateWindowScalar(window_y/window_x);
}

void TextHandler::UpdateZoom(afloat zoom) {
    zoom_x = window_x * zoom;
    zoom_y = window_y * zoom;
}

void TextHandler::UpdateOffset(afloat x, afloat y) {
    offset_x = x;
    offset_y = y;
}





void TextHandler::DrawText(std::string text, afloat in_x, afloat in_y, int align, float size, float r, float g, float b, float a) {
    // Scale down size
    size /= 1000;

    // Transform inputs from world space to camera space
    float x = ((in_x + offset_x)/zoom_x).convert_to<float>();
    float y = (-(in_y + offset_y)/zoom_y).convert_to<float>();

    // Account for alignment
    switch (align) {

    case ALIGN_LEFT:
        // No offset
        break;

    case ALIGN_CENTRE:
        // Half-width offset
        std::cout << Fonts::GetTextWidth(text, size) / 2 << "\n";
        x -= Fonts::GetTextWidth(text, size) / 2;
        break;

    case ALIGN_RIGHT: 
        // Width offset
        x -= Fonts::GetTextWidth(text, size);
        break;
    
    default:
        std::cout << "ERROR: Invalid alignment enum" << __LINE__ << "\n";
        break;
    }

    // Form TextObject
    text_objects.push_back(TextObject{text, x, y, size, r, g, b, a});
}


void TextHandler::Render()
{
    // Use shader
    shader.Use();

    // Prepare texture unit and bind VAO
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    // Iterate through all text objects
    for (TextObject text_object : text_objects) {

        // Handle text colour
        shader.SetVec4("textColor", text_object.r, text_object.g, text_object.b, text_object.a);

        // Iterate through all characters
        std::string::const_iterator c;
        for (c = text_object.text.begin(); c != text_object.text.end(); c++)
        {
            // Get character, calculate x, y, w and h
            Character character = Fonts::default_font[*c];

            float xpos = text_object.x + character.Bearing.x * text_object.size;
            float ypos = text_object.y - (character.Size.y - character.Bearing.y) * text_object.size;

            float w = character.Size.x * text_object.size;
            float h = character.Size.y * text_object.size;

            // Adjust for window size
            w *= window_y/window_x;

            // Send each character to the VBO
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };

            // Render glyph texture over a quad
            glBindTexture(GL_TEXTURE_2D, character.TextureID);

            // Update appropriate section of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            // Render said quad
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Advance to next glyph
            text_object.x += (character.Advance >> 6) * text_object.size * (window_y/window_x);
        }
    }

    // Unbind vertex array, unbind text unit
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Clear text pbject vector
    text_objects.clear();
}