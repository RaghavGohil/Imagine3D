#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

float gamma = 1/2.2;

void main()
{ 
    vec3 finalColor = pow(texture(screenTexture,TexCoords).rgb,vec3(gamma));
    FragColor = vec4(finalColor,1.0);
}