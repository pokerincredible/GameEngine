#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoord;                   

out vec2 pass_textureCoord;

void main(void){
    gl_Position = vec4(position, 1.0);
    pass_textureCoord.x = textureCoord.x;
    pass_textureCoord.y = textureCoord.y;
}