#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Norm;

out vec3 v_FragPos;
out vec3 v_Norm;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    v_FragPos = vec3(u_Transform * vec4(a_Position, 1.0));
    v_Norm = mat3(transpose(inverse(u_Transform))) * a_Norm;  
    
    gl_Position = u_ViewProjection * vec4(v_FragPos, 1.0);
}
