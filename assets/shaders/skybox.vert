#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoords = aPos; // The position serves as the direction vector for the cube
    vec4 finalPos = projection * view * vec4(aPos, 1.0);
    gl_Position = finalPos.xyww;
}