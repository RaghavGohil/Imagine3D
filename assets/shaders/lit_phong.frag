#version 330 core

out vec4 FragColor;
in vec2 tex;
in vec3 normal;
in vec3 vertexPos;

//texturing
uniform sampler2D texture1;

//light config
uniform vec3 lightPos;
vec3 lightColor = vec3(0.49, 0.89, 0.89);

//ambient
float ambientIntensity = 0.1f;
vec3 ambient = ambientIntensity * lightColor;

//specular
uniform vec3 viewPos;
float specularStrength = 1;

//attenuation
float attConst = 1.0f;
float linearConst = 0.09f; 
float quadConst = 0.04f;

void main() {
    
    //diffuse
    vec3 lightDir = normalize(lightPos - vertexPos);
    float diffuse = max(dot(lightDir,normal),0); 

    //specular
    vec3 viewDir = normalize(viewPos - vertexPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor;  

    //attenuation
    float d = length(lightPos - vertexPos);
    float att = 1.0f/(attConst + (linearConst*d) + (quadConst*pow(d,2)));

    vec3 finalColor = (ambient + diffuse + specular) * att; 
    FragColor = vec4(finalColor,1.0) * texture(texture1,tex); 
}