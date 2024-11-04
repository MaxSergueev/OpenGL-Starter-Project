#version 330 core
in vec3 pos;
in vec3 color;

uniform vec3 posShift;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(pos.x, -pos.y, pos.z, 1.0);
    ourColor = color;
}
