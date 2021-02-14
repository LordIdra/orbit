#version 330 core

layout (location = 0) in vec2 position_in;
layout (location = 1) in vec4 colour_in;

uniform mat4 transform_matrix;
out vec4 colour;

void main()
{
    gl_Position = transform_matrix * vec4(position_in.x, position_in.y, 0.0, 1.0);
    colour = colour_in;
}