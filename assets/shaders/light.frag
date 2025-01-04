#version 330 core

out vec4 FragColor;

vec3 lightColor = vec3(1.00, 0.91, 0.59);

void main() {
    FragColor = vec4(lightColor,1);
}