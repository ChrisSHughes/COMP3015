#version 460

in vec3 Colour;
in vec3 Vec;

layout (location = 0) out vec4 FragColor;
layout (binding = 0) uniform samplerCube SkyBoxTexture;
layout (binding = 1) uniform sampler2D NoiseTexture;

uniform float NoiseDensity = 1.8;
uniform float NoiseAggression = 0.2;

void main() {
    if (NoiseAggression > 0.0) {
        vec3 NoiseVector = normalize(Vec) * NoiseDensity;
        float NoiseValue = texture(NoiseTexture, NoiseVector.xy).r;
        NoiseValue = (NoiseValue - 0.4) * 1.8;

        vec3 TextureColour = texture(SkyBoxTexture, normalize(Vec)).rgb;
        TextureColour += NoiseValue * NoiseAggression;
        FragColor = vec4(Colour + TextureColour, 1.0);
    }
    else {
        FragColor = vec4(Colour, 1.0);
    }
}
