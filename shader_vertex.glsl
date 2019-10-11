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
   
    
    if (tp.z == 1.0) {

        float x = ((cos(time * 0.7) + 2) / 3) * tp.x;
        float y = ((cos(time * 0.7) + 2) / 3) * tp.y;
        
        tp = vec3(x, y, tp.z);
        
    }
    vertex_pos = tp;
	gl_Position = vec4(tp, 1.0);
}
