#ifndef BUD1_H
#define BUD1_H
#include "Models.h"
class bud1 : public MODELS {
public:
	void draw(ShaderProgram* sp, GLint textureUnits);
	void loadObj(string plik);
	void setup(const char* filenamepng, string filenameobj);

	GLuint TEX;
	glm::mat4 M;


	void move();
	float x_coord = 0.0f;
private:
	float speed = 20.0f;
	
	vector<glm::vec3> vertexes;
	vector<glm::vec4> normals;
	vector<glm::vec2> texcoords;
	vector<unsigned int> indices;
};

#endif // !BUD1_H
