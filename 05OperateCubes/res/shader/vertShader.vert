#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;                   

out vec2 pass_texCoord;

uniform mat4 transformationMatrix;

void main(void){
    gl_Position = transformationMatrix * vec4(position, 1.0);
    pass_texCoord.x = texCoord.x;
    pass_texCoord.y = 1 - texCoord.y;
}