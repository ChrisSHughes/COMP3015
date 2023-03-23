#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"
#include "helper/torus.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SceneBasic_Uniform : public Scene
{


private:
    glm::mat4 rotationMatrix;
    GLSLProgram prog;
    //GLuint vaoHandle;  // lab1
    //float angle;  // lab1

    Torus torus;

    void compile();
    void SetMatrices();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);


};

#endif // SCENEBASIC_UNIFORM_H
