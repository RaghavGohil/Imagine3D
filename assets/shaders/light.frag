#version 330 core

out vec4 FragColor;

vec3 lightColor = vec3(0.49, 0.89, 0.89);

void main() {
    FragColor = vec4(lightColor,1);
}