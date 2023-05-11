#include "scenebasic_uniform.h"
#include "helper/torus.h"
#include "helper/texture.h"

#include<glm/glm.hpp>
#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"

#include <glm/gtc/matrix_transform.hpp>;
#include "helper/noisetex.h"
using glm::vec3;
using glm::vec4;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.0f, 100, 100), angle(0.0f), tPrev(0.0f),
rotSpeed(glm::pi<float>() / 3.0f), sky(100.0f)
{
    ufo = ObjMesh::load("media/ufo.obj", true);
    ladymun = ObjMesh::load("media/ladymun.obj", true);

}


/// <summary>
/// read in model in init scene using a file reader lol
/// put that model into the VAO Array
/// </summary>

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);

    view = glm::lookAt(vec3(1.0f, 1.0f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);

    angle = glm::radians(360.0f);

    float x, z;

    // setting the unirforms for lights
    prog.setUniform("Light.Position", vec3(0.0f, 200.0f, 0.0f));
    prog.setUniform("Light.L", vec3(1.0f, 1.0f, 1.0f));
    prog.setUniform("Light.La", vec3(0.4f, 0.4f, 0.4f));
    prog.setUniform("Light.Ld", vec3(0.6f, 0.6f, 0.6f));
    prog.setUniform("Light.Ls", vec3(1.9f, 1.9f, 1.9f));

    //prog.setUniform("Lights[0].L", vec3(0.6f, 0.0f, 0.6f));
    //prog.setUniform("Lights[1].L", vec3(0.6f, 0.6f, 0.6f));
    //prog.setUniform("Lights[2].L", vec3(0.6f, 0.0f, 0.6f));
    
    
    //prog.setUniform("Lights[0].La", vec3(0.5f, 0.0f, 0.5f));
    //prog.setUniform("Lights[1].La", vec3(0.0f, 0.5f, 0.0f));
    //prog.setUniform("Lights[2].La", vec3(0.5f, 0.0f, 0.5f));

    //Setting the Uniforms for the Fog
    prog.setUniform("Fog.MaxDistance", 400.0f);
    prog.setUniform("Fog.MinDistance", 1.0f);
    prog.setUniform("Fog.Colour", vec3(0.0f,0.4f,0.02f));

    // Load in textures
    textureIDs[0] = Texture::loadTexture("../Project_Template/media/texture/grass/grass.png");
    textureIDs[1] = Texture::loadCubeMap("../Project_Template/media/texture/cubemap/skybox/sky");
    textureIDs[2] = Texture::loadTexture("../Project_Template/media/white.png");
    textureIDs[3] = Texture::loadTexture("../Project_Template/media/granite.png");

    noiseTexture = NoiseTex::generate2DTex(8.0f);
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    float deltaT = t - tPrev;

    if (tPrev == 0.0f) deltaT = 0.0f;

    tPrev = t;

    angle += rotSpeed * deltaT;

    if (angle > glm::two_pi<float>()) angle -= glm::two_pi<float>();

}

/// <summary>
/// bind vertex array
/// get matrices you want to send to the shader and lighting dfata (see last module for that)
/// call GL_DrawTriangles or whatever that is
/// same for next obj.
/// </summary>
void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);



    /// <summary>
    /// skybox render
    /// </summary>
    vec3 cameraPos = vec3(1.0f * cos(angle), 0.5f, 1.0f * sin(angle));
    view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    prog.setUniform("NoiseAggression", 0.2f);

    prog.use();
    model = mat4(1.0f);
    SetMatrices();

    // Activate and bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureIDs[1]);

    //do magic clouds
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);

    sky.render();

    
    /// <summary>
    /// object 1 - a ufo
    /// </summary>
    prog.setUniform("Material.Kd", 1.0f, 0.0f, 1.0f); // diffuse
    prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f); // spec
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.5f);  // ambient
    prog.setUniform("Material.Shininess", 15.0f);
    prog.setUniform("NoiseAggression", 0.0f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.25f, -0.4f, -0.2f));
    model = glm::rotate(model, glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.028f, 0.028f, 0.028f));
    SetMatrices();

    // Activate and bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIDs[2]);

    ufo->render();

    /// <summary>
    /// Objec 2 - womans head
    /// </summary>
    prog.setUniform("Material.Kd", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Ka", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Shininess", 200.0f);
    prog.setUniform("NoiseAggression", 0.0f);


    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.25f, 0.17f, -0.2f));
    model = glm::rotate(model, glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    SetMatrices();

    // Activate and bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIDs[3]);

    ladymun->render();


    /// <summary>
    /// object 3 - the plane
    /// </summary>
    prog.setUniform("Material.Kd", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Ks", 0.6f, 0.6f, 0.3f);
    prog.setUniform("Material.Ka", 0.7f, 0.7f, 0.7f);
    prog.setUniform("Material.Shininess",180.5f);
    prog.setUniform("NoiseAggression", 0.0f);


    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, vec3(0.6f, 0.6f, 0.6f));
    SetMatrices();

    // Activate and bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);

    plane.render();

}

void SceneBasic_Uniform::SetMatrices() 
{
    mat4 mv(view * model);
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
    
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}
