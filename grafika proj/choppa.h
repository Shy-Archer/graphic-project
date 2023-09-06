#ifndef CHOPPA_H
#define CHOPPA_H
#include "Models.h"
class choppa : public MODELS
{public:
	void draw(ShaderProgram* sp, GLint textureUnits);
	void loadObj(string plik);
	void setup(const char* filenamepng, string filenameobj);

	GLuint TEX;
	glm::mat4 M;


	void move();

	

private:
		float speed = 40.0f;
	   float x_coord = 0.0f;
	   vector<glm::vec3> vertexes;
	   vector<glm::vec4> normals;
	   vector<glm::vec2> texcoords;
	   vector<unsigned int> indices;
};


#endif
