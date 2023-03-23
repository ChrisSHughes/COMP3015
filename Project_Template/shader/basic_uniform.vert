#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 Colour;

uniform vec3 Ld;
uniform vec4 LightPosition;

uniform mat3 NormalMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

uniform struct LightInfo
{
    vec4 Position; // light pos in eye coords
    vec3 La; //Ambient Light intensity
    vec3 L; // defuse and spec light intensity
} Lights[3];

uniform struct MaterialInfo
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;
} Material;


vec3 PhongModel (int light, vec3 position, vec3 n)
{
    //calculate ambient here, to access each La light value

    vec3 ambient = Material.Ka * Lights[light].La;

    vec3 s = vec3(Lights[light].Position) - ( VertexPosition * Lights[light].Position.w ); //find out s vector

        float sDotN = max(dot(n, s), 0.0); //calculate dot product between s & n
    vec3 diffuse = Material.Kd * sDotN;

    //calculate specular here
    vec3 spec = vec3(0.0);
    
    if( sDotN > 0.0 )
    {
        vec3 v = normalize(-position.xyz);
        vec3 r = reflect( -s, n );
        spec = Material.Ks * pow( max( dot(r,v), 0.0 ),
        Material.Shininess);
    }

    return ambient + Lights[light].L * (diffuse + spec);
}

void main()
{
    vec3 n = normalize( NormalMatrix * VertexNormal );
    vec4 p = normalize( ModelViewMatrix * vec4( VertexPosition, 1.0 ) );

    vec3 camCoords = vec3(0.0);

    Colour = vec3(0.0);
    for (int i = 0; i < 3; i++)
    {
        Colour += PhongModel(i, camCoords, n);
    }

    gl_Position = MVP * vec4(VertexPosition,1.0);
}
