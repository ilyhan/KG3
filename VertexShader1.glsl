#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragLightPos; 
out vec3 fragPos; // ����� ���������� ��� ������� ���������

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos; 

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragColor = color;
    fragNormal = mat3(transpose(inverse(model))) * normal;
    fragLightPos = lightPos;
    fragPos = vec3(model * vec4(position, 1.0)); 
}
