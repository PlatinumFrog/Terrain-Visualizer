#ifndef TERRAIN_TEXTURE
#define TERRAIN_TEXTURE

#include <SDL.h>
#ifdef _DEBUG
#include "../gladDebug/include/glad.h"
#else
#include "../gladRelease/include/glad.h"
#endif
#include <SDL_opengl.h>
#include "Input.h"

class TerrainTexture {
	static const float squareCoords[8];
	GLuint vboID, vaoID, heightMapTexID, shadowMapTexID, drawShaderID, shadowShaderID;

public:
	TerrainTexture() {
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareCoords), squareCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};

	~TerrainTexture();

	void draw();

};

const float TerrainTexture::squareCoords[8] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
};

#endif