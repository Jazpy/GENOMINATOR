#version 400 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec3 vert_color;
out vec3 frag_color;

uniform mat4 Projection;
uniform mat4 Modelview;

void main()
{
	gl_Position = Projection * Modelview * Position;
	frag_color = vert_color;
}

