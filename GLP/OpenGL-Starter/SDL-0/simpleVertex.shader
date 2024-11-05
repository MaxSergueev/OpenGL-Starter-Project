#version 330 core
in vec3 pos;
in vec3 color;

uniform vec3 offSet;
uniform float scale;

out vec3 ourColor;
out vec3 fragPos;

void main()
{
    gl_Position = vec4((pos.x) + offSet.x, (pos.y) + offSet.y, pos.z, 1.0);
    
    //fragPos = pos;
    ourColor = color;
}
