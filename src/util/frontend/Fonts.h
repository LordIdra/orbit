#pragma once

#include <iostream>
#include <map>
#include <string>

#include <glm/glm.hpp>
#include <ft2build.h>
#include <glad/glad.h>

#include FT_FREETYPE_H

using std::map;
using std::string;



struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};


class Fonts {
public:
    static map<char, Character> LoadFont(string location);
    static void InitializeFonts();
    static map<char, Character> shentox;
};