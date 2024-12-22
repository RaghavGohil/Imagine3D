#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec2 tex;
out vec3 normal;
out vec3 vertexPos;

uniform mat4 projection; 
uniform mat4 view; 
uniform mat4 model; 

void main() {
    tex = aTex;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    normal = aNormal;
    vertexPos = vec3(model * vec4(aPos, 1.0));
}