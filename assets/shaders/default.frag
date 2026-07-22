#version 410 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

struct Light {
    vec3 Color;
    vec3 Ambient;
    vec3 Direction;
};

uniform Material uMaterial;
uniform Light uLight;

uniform vec3 uViewPosition;

void main() {
    vec3 normal = normalize(Normal);
    vec3 direction = normalize(-uLight.Direction);
    vec3 viewPos = normalize(uViewPosition - FragPos);
    vec3 halfway = normalize(direction + viewPos);

    vec3 ambient = uLight.Ambient * uMaterial.Diffuse;

    float diffuseFactor = max(dot(normal, direction), 0.0);
    vec3 diffuse = uLight.Color * uMaterial.Diffuse * diffuseFactor;

    float specularFactor = pow(max(dot(normal, halfway), 0.0), uMaterial.Shininess);
    specularFactor *= step(0.0, diffuseFactor);

    vec3 specular = uLight.Color * uMaterial.Specular * specularFactor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
