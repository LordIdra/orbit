#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>



// 'Raise' a generic error which outputs line, file, error and then pauses the 
// program until a key is pressed
#define raise_gl_error(error)\
    std::cout << "=====[ERROR]=====" << "\n";\
    std::cout << "FILE: " << __FILE__ << "\n";\
    std::cout << "LINE: " << __LINE__ << "\n";\
    std::cout << error << "\n";\
    system("pause");



struct Shader {
    
    unsigned int ID = 0;

    Shader() = default;
    Shader(std::string vertex_path, std::string fragment_path);

    void Use();

    unsigned int UniformLocation(const char* name);

    void SetInt(const char* location, int value);
    void SetFloat(const char* location, float value);
    void SetVec2(const char* location, float value1, float value2);
    void SetVec3(const char* location, float value1, float value2, float value3);
    void SetVec4(const char* location, float value1, float value2, float value3, float value4);
    void SetMat2(const char* location, unsigned int count, float *matrix_pointer);
    void SetMat3(const char* location, unsigned int count, float *matrix_pointer);
    void SetMat4(const char* location, unsigned int count, float *matrix_pointer);
};