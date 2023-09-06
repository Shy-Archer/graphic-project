#ifndef SMIGLO_H
#define SMIGLO_H

#include "choppa.h"
class smiglo : public choppa {
public:
	void draw(ShaderProgram* sp, GLint textureUnits, glm::mat4 Mp);
	void loadObj(string plik);
	void setup(const char* filenamepng, string filenameobj);
	void move();
	float angle =0;
	float speed = 3.14f/2;
	GLuint TEX;
	glm::mat4 M1;
private:
	vector<glm::vec3> vertexes;
	vector<glm::vec4> normals;
	vector<glm::vec2> texcoords;
	vector<unsigned int> indices;
};
#endif
