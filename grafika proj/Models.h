#ifndef MODELS_H
#define MODELS_H
#include "shaderprogram.h"
#include "lodepng.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using namespace std;
class MODELS
{
public:
	MODELS();
	~MODELS(); 
	float angle_x;
	float angle_y;
	void loadObj(string plik);
	void setup(const char* filenamepng, string filenameobj);
	
	GLuint readTexture(const char* filename);
//	virtual void move();
	GLuint TEX;
	virtual void draw(ShaderProgram *sp,GLint textureUnits);
	glm::mat4 M;
	float velocity = 10.0f;
	float gravity = 9.8f;
	float y_coord = -1.0f;
private:
	
	
	vector<glm::vec3> vertexes;
	vector<glm::vec4> normals;
	vector<glm::vec2> texcoords;
	vector<unsigned int> indices;
};

#endif // !MODELS_H

