#version 330 core
out vec3 color;

in vec3 vertex_pos;
in vec3 vertex_color;

void main()
{
    //distance point is from center
    float factor = sqrt(pow(vertex_pos.x - 0.0, 2) + pow(vertex_pos.y - 0.0, 2));
        
    //coloring for background
    color = vec3(0, 0, 1 - (0.6 * factor));
}
