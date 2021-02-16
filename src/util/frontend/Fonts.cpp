#include "Fonts.h"




map<char, Character> Fonts::default_font = map<char, Character>();
float Fonts::window_scalar = 1;


map<char, Character> Fonts::LoadFont(string location)
{
    /* https://learnopengl.com/In-Practice/Text-Rendering */
    FT_Library font_library;
    if (FT_Init_FreeType(&font_library)) std::cout << "ERROR: Failed to initialize FreeType Library " << __LINE__ << "\n";

    FT_Face face;
    if (FT_New_Face(font_library, location.c_str(), 0, &face)) std::cout << "ERROR: Failed to load face " << __LINE__ << "\n";

    FT_Set_Pixel_Sizes(face, 0, 48);  
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) std::cout << "ERROR: Failed to load glyphs " << __LINE__ << "\n";
    
    std::map<char, Character> characters;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    for (unsigned char c = 0; c < 128; c++) {

        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR: Failed to load glyph " << __LINE__ << "\n";
            continue;
        }

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character for later use
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };

        characters.insert(std::pair<char, Character>(c, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Done_Face(face);
    FT_Done_FreeType(font_library);

    return characters;
}


void Fonts::UpdateWindowScalar(float scalar) {
    Fonts::window_scalar = scalar;
}


void Fonts::InitializeFonts() {
    Fonts::default_font = LoadFont("../fonts/ARIAL.TTF");
}


float Fonts::GetTextWidth(string text, float size) {
    // Iterate through text and return the total size that it will take on the screen
    float total_width = 0;
    std::string::const_iterator c;

    for (c = text.begin(); c != text.end(); c++) {
        total_width += Fonts::default_font[*c].Advance * size * window_scalar;
    }

    return total_width / 64;
}