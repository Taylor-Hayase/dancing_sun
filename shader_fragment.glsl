#version 330 core
out vec3 color;

in vec3 vertex_pos;
in vec3 vertex_color;

void main()
{
        //distance point is from center
        float factor = sqrt(pow(vertex_pos.x - 0.0, 2) + pow(vertex_pos.y - 0.0, 2));

        //center of sun
        if (factor <= 0.3) {
            color = vertex_color;
        }
        else {
            //coloring for sun rays
            float r = vertex_color.r + (0.3 * factor);
            float g = vertex_color.g + (0.3 * factor);
            float b = vertex_color.b;
        
            color = vec3(r, g, b);
        }
}
