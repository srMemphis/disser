#version 330 core
			
layout(location = 0) out vec4 diffuseColor;

uniform vec4 u_Color;

void main()
{
	diffuseColor = u_Color;
}
