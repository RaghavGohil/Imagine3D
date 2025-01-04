#version 330 core

// Output fragment color
out vec4 FragColor;

// Inputs from the vertex shader
in vec2 TexCoords;        // Texture coordinates
in vec3 FragPos;          // Fragment position in world space
in mat3 TBN;              // Tangent-Bitangent-Normal matrix

// Texture samplers
uniform sampler2D texture_diffuse1;  // Diffuse map
uniform sampler2D texture_specular1; // Specular map (optional)
uniform sampler2D texture_normal1;   // Normal map

// Lighting properties
uniform vec3 lightPos;    // Position of the light source in world space
uniform vec3 viewPos;     // Position of the camera in world space
uniform vec3 lightColor;  // Color of the light
uniform float shininess;  // Shininess for specular reflection (higher = sharper highlights)

// Ambient lighting
const float ambientIntensity = 0.1;  // Strength of ambient lighting

// Attenuation constants
const float attConst = 1.0;   // Constant attenuation
const float linearConst = 0.09;  // Linear attenuation
const float quadConst = 0.032;   // Quadratic attenuation

void main() {
    // Discard fragments with zero alpha (transparent areas)
    if (texture(texture_diffuse1, TexCoords).a == 0.0)
        discard;

    // Retrieve normal from the normal map and transform to world space
    vec3 normal = texture(texture_normal1, TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0); // Convert from [0,1] to [-1,1]
    normal = normalize(TBN * normal);       // Transform to world space using TBN

    // Calculate light direction and view direction
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // ** Ambient Lighting **
    vec3 ambient = ambientIntensity * lightColor * texture(texture_diffuse1, TexCoords).rgb;

    // ** Diffuse Lighting **
    float diffStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffStrength * lightColor * texture(texture_diffuse1, TexCoords).rgb;

    // ** Specular Lighting (Blinn-Phong Model) **
    vec3 halfwayDir = normalize(lightDir + viewDir); // Halfway vector
    float specStrength = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = specStrength * lightColor * texture(texture_specular1, TexCoords).rgb;

    // ** Attenuation **
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (attConst + linearConst * distance + quadConst * distance * distance);

    // Apply attenuation to diffuse and specular components
    diffuse *= attenuation;
    specular *= attenuation;

    // Combine lighting components
    vec3 lighting = ambient + diffuse + specular;

    // Output final color
    FragColor = vec4(lighting, 1.0);
}
