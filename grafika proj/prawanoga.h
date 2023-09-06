#ifndef PRAWANOGA_H
#define PRAWANOGA_H
#include "Models.h"
class prawanoga : public MODELS {
public:

	void draw(ShaderProgram* sp, GLint textureUnits, glm::mat4 Mp);
	void loadObj(string plik);
	void setup(const char* filenamepng, string filenameobj);

	GLuint TEX;
	glm::mat4 M1;
private:


	vector<glm::vec3> vertexes;
	vector<glm::vec4> normals;
	vector<glm::vec2> texcoords;
	vector<unsigned int> indices;
};
#endif





