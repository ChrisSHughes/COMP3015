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
using glm::vec3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() : plane(10.0f, 10.0f, 100, 100) 
{
    ufo = ObjMesh::load("../Project_Template/media/ufo.obj", true);
    ladymun = ObjMesh::load("../Project_Template/media/ladymun.obj", true);

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

    float x, z;
    //for (int i = 0; i < 3; i++)
    //{
    //    std::stringstream name;
    //    name << "Lights[" << i << "].Position";
    //    x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
    //    z = 3.0f * sinf((glm::two_pi<float>() / 3) * i);
    //    prog.setUniform(name.str().c_str(), view * glm::vec4(x, 3.2f, z + 3.0f, 1.0f));
    //}

    prog.setUniform("Light.Position", vec3(0.0f, 200.0f, 0.0f));
    prog.setUniform("Light.L", vec3(1.0f, 1.0f, 1.0f));
    prog.setUniform("Light.La", vec3(0.4f, 0.4f, 0.4f));
    prog.setUniform("Light.Ld", vec3(0.6f, 0.6f, 0.6f));
    prog.setUniform("Light.Ls", vec3(20.9f, 20.9f, 20.9f));
    //prog.setUniform("Lights[0].L", vec3(0.6f, 0.0f, 0.6f));
    //prog.setUniform("Lights[1].L", vec3(0.6f, 0.6f, 0.6f));
    //prog.setUniform("Lights[2].L", vec3(0.6f, 0.0f, 0.6f));
    
    
    //prog.setUniform("Lights[0].La", vec3(0.5f, 0.0f, 0.5f));
    //prog.setUniform("Lights[1].La", vec3(0.0f, 0.5f, 0.0f));
    //prog.setUniform("Lights[2].La", vec3(0.5f, 0.0f, 0.5f));


#pragma region Lab1 Code - Render Triangle from set info


    //lab 1 stuff
    //std::cout << std::endl;

    //prog.printActiveUniforms();

    ///////////////////// Create the VBO ////////////////////
    //float positionData[] = {
    //    -0.8f, -0.8f, 0.0f,
    //     0.8f, -0.8f, 0.0f,
    //     0.0f,  0.8f, 0.0f };
    //float colorData[] = {
    //    1.0f, 0.0f, 0.0f,
    //    0.0f, 1.0f, 0.0f,
    //    0.0f, 0.0f, 1.0f };

    //// Create and populate the buffer objects
    //GLuint vboHandles[2];
    //glGenBuffers(2, vboHandles);
    //GLuint positionBufferHandle = vboHandles[0];
    //GLuint colorBufferHandle = vboHandles[1];

    //glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    //glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    //glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

    //// Create and set-up the vertex array object
    //glGenVertexArrays( 1, &vaoHandle );
    //glBindVertexArray(vaoHandle);

    //glEnableVertexAttribArray(0);  // Vertex position
    //glEnableVertexAttribArray(1);  // Vertex color

    //#ifdef __APPLE__
    //    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    //    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

    //    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    //    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
    //#else
    //		glBindVertexBuffer(0, positionBufferHandle, 0, sizeof(GLfloat)*3);
    //		glBindVertexBuffer(1, colorBufferHandle, 0, sizeof(GLfloat)*3);

    //		glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
    //		glVertexAttribBinding(0, 0);
    //		glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
    //	  glVertexAttribBinding(1, 1);
    //#endif
    //glBindVertexArray(0);
#pragma endregion

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



}

/// <summary>
/// bind vertex array
/// get matrices you want to send to the shader and lighting dfata (see last module for that)
/// call GL_DrawTriangles or whatever that is
/// same for next obj.
/// </summary>
void SceneBasic_Uniform::render()
{
#pragma region Lab 1 code

    //glClear(GL_COLOR_BUFFER_BIT);
    //
    //GLuint programHandle = prog.getHandle();
    //rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, vec3(0.0f, 0.0f, 1.0f));
    //GLuint location = glGetUniformLocation(programHandle, "RotationMatrix");
    //glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);

    //glBindVertexArray(vaoHandle);
    //glDrawArrays(GL_TRIANGLES, 0, 3 );

    //glBindVertexArray(0);
#pragma endregion

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    /// <summary>
    /// object 1 - a ufo
    /// </summary>
    prog.setUniform("Material.Kd", 1.0f, 0.0f, 1.0f); // diffuse
    prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.0f); // spec
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.5f);  // ambient
    prog.setUniform("Material.Shininess", 15.0f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.25f, -0.4f, -0.2f));
    model = glm::rotate(model, glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
    SetMatrices();
    ufo->render();

    /// <summary>
    /// Objec 2 - woman
    /// </summary>
    prog.setUniform("Material.Kd", 0.1f, 1.5f, 0.1f);
    prog.setUniform("Material.Ks", 1.0f, 1.0f, 1.5f);
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 25.0f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.4f, 0.18f, -0.4f));
    model = glm::rotate(model, glm::radians(35.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
    SetMatrices();
    ladymun->render();


    /// <summary>
    /// object 3 - the plane
    /// </summary>
    prog.setUniform("Material.Kd", 0.8f, 0.0f, 0.0f);
    prog.setUniform("Material.Ks", 0.3f, 0.9f, 0.3f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.8f);
    prog.setUniform("Material.Shininess", 5.5f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.55f, 0.0f));
    SetMatrices();
    GLuint texID = Texture::loadTexture("../Project_Template/media/Grass.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
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
