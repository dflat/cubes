#version 330 core
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Ambient lighting
    float ambientStrength = 0.02;//72;
    vec3 ambient = ambientStrength * ourColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ourColor;

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
}
