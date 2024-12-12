#version 330 core
in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragLightPos;
in vec3 fragPos; // Новая переменная для позиции фрагмента

out vec4 color;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(fragLightPos - fragPos); // Исправлено

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseColor = diff * vec3(1.0, 1.0, 1.0); 

    color = vec4(fragColor * diffuseColor, 1.0);
}
