#version 460

in vec3 Color;
in vec3 LightIntensity;

layout (location = 0) out vec4 FragColor;

void main() {
    vec3 finalColor = Color * LightIntensity;
    FragColor = vec4(LightIntensity, 1.0);
}
