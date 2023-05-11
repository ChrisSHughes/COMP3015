#version 460

in vec3 Colour;
in vec3 Vec;

layout (location = 0) out vec4 FragColor;
layout (binding = 0) uniform samplerCube SkyBoxTexture;

void main() {
    vec3 TexColour = texture(SkyBoxTexture, normalize(Vec)).rgb;
    FragColor = vec4(Colour + TexColour, 1.0);
}
