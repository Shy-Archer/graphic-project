#include "smiglo.h"


void smiglo::loadObj(std::string plik) {

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(plik,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
	cout << importer.GetErrorString() << endl;
	aiMesh* mesh = scene->mMeshes[0];
	for (int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D vertex = mesh->mVertices[i];
		vertexes.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
		aiVector3D normal = mesh->mNormals[i]; //Wektory znormalizowane
		normals.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

		aiVector3D texCoord = mesh->mTextureCoords[0][i];
		texcoords.push_back(glm::vec2(texCoord.x, texCoord.y));
	}
	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace& face = mesh->mFaces[i]; //face to jeden z wielok¹tów siatki
		//dla ka¿dego indeksu->wierzcho³ka tworz¹cego wielok¹t
		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}

	}
}
void smiglo::move() {
	angle -= speed * glfwGetTime();
}
void smiglo::setup(const char* filenamepng, string filenameobj) {

	TEX = readTexture(filenamepng);
	loadObj(string(filenameobj));
}
void smiglo::draw(ShaderProgram* sp, GLint textureUnits, glm::mat4 Mp) {
	M1 = Mp;
	//M1 = glm::rotate(Mp, 90.0f * 3.14F / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f)); //Compute model matrix

	M1 = glm::rotate(Mp, angle*20, glm::vec3(0.0f, 0.1f, 0.0f));
	M1 = glm::translate(M1, glm::vec3(2.5f, -25.0f, 0.0f));

	//Compute model matrix

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M1));


	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertexes.data());
	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals.data());
	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"),
		2, GL_FLOAT, false, 0, texcoords.data());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TEX);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord0"));

	glDisableVertexAttribArray(sp->a("normal"));
}