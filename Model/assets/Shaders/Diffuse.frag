#version 460 core
layout(location = 0) out vec4 diffuseColor;

in vec3 v_Norm;  
in vec3 v_FragPos;  
  
uniform vec3 lightPos;
uniform vec3 staticLightPos = vec3(10, 10, 10);

uniform vec3 lightColor = vec3(0.1, 0.6, 0.7);
uniform vec3 staticLightColor = vec3(0.1, 0.95, 0.5);

vec3 objectColor = vec3(0.5, 0.5, 0.5);

void main()
{
    // ambient color
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * objectColor;
  	
    // difuse color
    vec3 norm = normalize(v_Norm);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // static difuse color
    lightDir = normalize(staticLightPos - v_FragPos);
    diff = max(dot(norm, lightDir), 0.0);
    vec3 staticDiffuse = diff * staticLightColor;


    vec3 result = (ambient + diffuse + staticDiffuse) * objectColor;
    diffuseColor = vec4(result, 1.0);
}