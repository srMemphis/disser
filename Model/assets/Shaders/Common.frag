#version 330 core
			
layout(location = 0) out vec4 diffuseColor;

in vec3 v_Position;

void main()
{
	//diffuseColor = vec4(v_Position * 0.5 + 0.5, 1.0);
	diffuseColor = vec4(1.0, 1.0, 1.0, 0.5);
}
