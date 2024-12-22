#version 330 core

out vec4 FragColor;
in vec2 tex;
in vec3 normal;
in vec3 vertexPos;

//texturing
uniform sampler2D texture1;

//light config
uniform vec3 lightPos;
vec3 lightColor = vec3(1,1,1);

//ambient
float ambientIntensity = 0.1f;
vec3 ambient = ambientIntensity * lightColor;

//specular
uniform vec3 viewPos;
uniform vec3 front;
float specularStrength = 1;

//attenuation
float attConst = 1.0f;
float linearConst = 0.09f; 
float quadConst = 0.04f;

//spot light
float angle = cos((15.0 * 3.142) / 180); 

void main() {

    //diffuse
    vec3 lightDir = normalize(viewPos - vertexPos);
    float diffuse = max(dot(lightDir,normal),0); 

    //specular
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(lightDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    //attenuation
    float d = length(viewPos - vertexPos);
    float att = 1.0f/(attConst + (linearConst*d) + (quadConst*pow(d,2)));

    //spot
    // real cool stuff, this is essentially the cosQ function itself, since magnitudes are 1 for both vecs (but we get the vector angle here)
    float currAngle = dot(front, normalize(-lightDir));

    vec3 finalColor;
    if(currAngle > angle){
        finalColor = (ambient + diffuse + specular) * att; 
        //finalColor = vec3(0,1,0);
    }
    else{
        finalColor = ambient; 
    }
    FragColor = vec4(finalColor,1.0) * texture(texture1,tex); 
}