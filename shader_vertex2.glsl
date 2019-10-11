#version 330 core
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertCol;

uniform float time;

out vec3 vertex_pos;
out vec3 vertex_color;

void main()
{
    vertex_color = vertCol;
    
    vec3 tp = vertPos;
    vertex_pos = tp;
    
	gl_Position = vec4(vertPos, 1.0);
}
