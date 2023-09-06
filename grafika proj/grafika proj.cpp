#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaderprogram.h"
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "lodepng.h"
#include "Models.h"
#include "noga.h"
#include "prawanoga.h"
#include "bud1.h"
#include "bud2.h"
#include "bud3.h"
#include "choppa.h"
#include "smiglo.h"

using namespace std;
int flag = 1;
float aspectRatio;
GLint textureUnits;
GLint textureUnits1;
const float PI = 3.14f;
choppa heli;
smiglo smig;
ShaderProgram* sp;
MODELS Bezkonczyn;
//noga nogaL;
//prawanoga nogaP;
bud1 budynek;
bud2 budynek2;
bud3 budynek3;

glm::vec3 cameraPos = glm::vec3(38.0f, 10.0f, -46.0f);

glm::vec3 cameraFront = glm::vec3 (-0.68f,-0.3f,0.69f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 V;
/*float lastX = 960, lastY = 540;
float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;*/



void jump() {
    if (budynek.x_coord > 7.1f)
    {
        flag = 0;
    }

    if (flag == 0 && ((budynek2.x_coord < 61.1f && budynek2.x_coord >20.0f) || (budynek.x_coord < 170.1f && budynek.x_coord >136.0f) || (budynek.x_coord < 7.1f) || (budynek3.x_coord < 109.1f && budynek3.x_coord >68.15f)))
    {
        Bezkonczyn.y_coord += Bezkonczyn.velocity * glfwGetTime();
        Bezkonczyn.velocity -= Bezkonczyn.gravity * glfwGetTime();


    }
    if ((budynek2.x_coord > 61.1f || budynek2.x_coord < 20.0f) && (budynek.x_coord > 170.1f || budynek.x_coord < 136.0f) && budynek.x_coord > 7.1f && (budynek3.x_coord > 109.1f || budynek3.x_coord < 68.15f)) {
        if (Bezkonczyn.y_coord < -0.95f) {
            Bezkonczyn.velocity = 10.5f;
        }
        else { Bezkonczyn.velocity = 10.0f; }
    }
    



}
void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

float speed_x;
float speed_y;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
    const float cameraSpeed = 1.0f; 

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
   /* if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/
    
   
}
/*void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
*/
void windowResizeCallback(GLFWwindow* window, int width, int height) {
    if (height == 0) return;
    glViewport(0, 0, width, height);
}
void initOpenGLProgram(GLFWwindow* window) {

    glClearColor(105.0f / 255.0f, 105.0f / 255.0f, 105.0f / 255.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);// pozwala na kontrolowanie obiektów w zależności od odległości

    glfwSetWindowSizeCallback(window, windowResizeCallback);//ustawienie wielkości okna
    //glfwSetCursorPosCallback(window, mouse_callback);
   // glfwSetKeyCallback(window, keyCallback);//ustawienie klawiszy


    sp = new ShaderProgram("V_simp.glsl", NULL, "F_simp.glsl");
    Bezkonczyn.setup("ghost.png", "ghost.obj");
    heli.setup("cartoon_helicopter.png","parakopter.obj");
    budynek2.setup("T_Electrical_Substation_BaseColor.png", "uploads_files_2891761_Electrical_Substation.obj");
    budynek.setup("free_building_d.png", "free_building.obj");
    budynek3.setup("bud3.png","bud3.obj");
    smig.setup("cartoon_helicopter.png","smiglo.obj");
  
}
void freeOpenGLProgram(GLFWwindow* window) {
   
    delete sp;
   
    glDeleteTextures(1, &Bezkonczyn.TEX);
    
    glDeleteTextures(1, &budynek.TEX);
    glDeleteTextures(1, &budynek2.TEX);
    glDeleteTextures(1, &budynek3.TEX);
    glDeleteTextures(1, &smig.TEX);
    glDeleteTextures(1, &heli.TEX);
}

void drawScene(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 
    glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, 1.0f, 1.0f, 300.0f); 
   
    sp->use();

    glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
    
    
  Bezkonczyn.draw(sp, textureUnits);
    
    budynek.draw(sp, textureUnits);
    budynek2.draw(sp, textureUnits);
    budynek3.draw(sp, textureUnits);
    heli.draw(sp,textureUnits);
    smig.draw(sp,textureUnits,heli.M);
    glfwSwapBuffers(window); 
   
}

int main()
{

    GLFWwindow* window; 

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "Can't initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

    window = glfwCreateWindow(1920, 1080, "Ghost-Jumper", NULL , NULL);  

    if (!window) 
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); 
    glfwSwapInterval(1); 

    GLenum err;
    if ((err = glewInit()) != GLEW_OK) { 
        fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window); 
   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   


    glfwSetTime(0); 
    while (!glfwWindowShouldClose(window)) 
    {

        
        budynek.move();
        budynek2.move();
        budynek3.move();
        heli.move();
        smig.move();
        jump();
       
        glfwSetTime(0); 
        drawScene(window); 
        glfwPollEvents(); 
    }
    freeOpenGLProgram(window);

    glfwDestroyWindow(window); 
    glfwTerminate(); 
    exit(EXIT_SUCCESS);

}
