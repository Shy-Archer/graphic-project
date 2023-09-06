#ifndef BUD3_H
#define BUD3_H
#include "MODELS.h"
class bud3 : public MODELS{
public:
	void draw(ShaderProgram* sp, GLint textureUnits);
	void loadObj(string plik);
	void setup(const char* filenamepng, string filenameobj);
	
	float angle_y;
	float angle_x;
	GLuint TEX;
	glm::mat4 M1;
	float x_coord = 0.0f;
	void move();
private:
	float speed = 20.0f;
	


	vector<glm::vec3> vertexes;
	vector<glm::vec4> normals;
	vector<glm::vec2> texcoords;
	vector<unsigned int> indices;
};
#endif