#version 330 core
out vec4 FragColor;
uniform vec4 redShift;

void main()
{
    FragColor = redShift;
}