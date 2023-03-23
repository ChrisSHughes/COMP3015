#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;

out vec3 Color;
out vec3 LightIntensity;

uniform vec3 Kd;
uniform vec3 Ld;
uniform vec4 LightPosition;

uniform mat3 NormalMatrix;
uniform mat4 RotationMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;


void main()
{
    vec3 n = normalize( NormalMatrix * VertexNormal );
    vec4 p = normalize( ModelViewMatrix * vec4( VertexPosition, 1.0 ) );

    float diff = max( dot( n, Ld ), 0.0 );
    LightIntensity = diff * Kd;

    gl_Position = vec4(VertexPosition,1.0) * MVP;
}
