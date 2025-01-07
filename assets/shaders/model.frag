#version 330 core

// Output fragment color
out vec4 FragColor;

// Inputs from the vertex shader
in vec2 TexCoords;        // Texture coordinates
in vec3 FragPos;          // Fragment position in world space
in mat3 TBN;              // Tangent-Bitangent-Normal matrix

// Texture samplers
uniform sampler2D texture_diffuse1;  // Diffuse map
uniform sampler2D texture_specular1; // Specular map
uniform sampler2D texture_normal1;   // Normal map

// Lighting properties
uniform vec3 lightPos;    // Light position in world space
uniform vec3 viewPos;     // Camera position in world space
vec3 lightColor = vec3(1);  // Light color
float shininess = 32.0;  // Shininess (higher = sharper highlights)

// Attenuation constants
const float attConst = 1.0;
const float linearConst = 0.09;
const float quadConst = 0.032;

// Gamma correction constant
const float gamma = 1.0 / 2.2;

void main() {
    // Discard fragments with alpha = 0 in the diffuse texture
    if (texture(texture_diffuse1, TexCoords).a == 0.0) {
        discard;
    }

    // Retrieve normal from the normal map and transform to world space
    vec3 normal = texture(texture_normal1, TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0); // Convert from [0,1] to [-1,1]
    normal = normalize(TBN * normal);       // Transform to world space using TBN

    // Light direction and view direction
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Ambient lighting
    vec3 ambient = 0.02 * lightColor * texture(texture_diffuse1, TexCoords).rgb;

    // Diffuse lighting
    float diffStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffStrength * lightColor * texture(texture_diffuse1, TexCoords).rgb;

    // Specular lighting (Blinn-Phong Model)
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float specStrength = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = specStrength * lightColor * texture(texture_specular1, TexCoords).rgb;

    // Attenuation
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (attConst + linearConst * distance + quadConst * distance * distance);

    // Combine all components with attenuation
    vec3 lighting = attenuation * (ambient + diffuse + specular);

    // Gamma correction
    lighting = pow(lighting, vec3(gamma));

    // Output final color
    FragColor = vec4(lighting, 1.0);
}
