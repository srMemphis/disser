#version 460 core
layout(location = 0) out vec4 diffuseColor;

in vec3 v_Norm;  
in vec3 v_FragPos;  
  
vec3 lightPos = vec3(0,10,10); 

vec3 lightColor = vec3(0.7, 0.6, 0.2);
vec3 objectColor = vec3(0.5, 0.5, 0.5);

void main()
{
    // Îêðóæàþùàÿ ñîñòàâëÿþùàÿ
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * objectColor;
  	
    // Äèôôóçíàÿ ñîñòàâëÿþùàÿ 
    vec3 norm = normalize(v_Norm);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
        
    vec3 result = (ambient + diffuse) * objectColor;
    diffuseColor = vec4(result, 1.0);
} 