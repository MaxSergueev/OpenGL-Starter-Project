#version 330 core
//in vec3 ourColor;
in vec3 fragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(clamp(fragPos, 0.0, 1.0), 1.0);
}
