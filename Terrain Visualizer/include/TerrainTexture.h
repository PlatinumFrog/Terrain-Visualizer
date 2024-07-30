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
#include "Shader.h"

class TerrainTexture {
	static const float squareCoords[8];
	GLuint vboID, vaoID, heightMapTexID, shadowMapTexID, drawShaderID, shadowShaderID;

public:
	TerrainTexture():
		vboID(0),
		vaoID(0),
		heightMapTexID(0),
		shadowMapTexID(0),
		drawShaderID(Shaders::compileShader("flatSquare.vert", "flatSquare.frag")),
		shadowShaderID(0)
	{
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

	~TerrainTexture() {
		glDeleteBuffers(1, &vboID);
		glDeleteVertexArrays(1, &vaoID);
		glDeleteProgram(drawShaderID);
	}

	void draw() {
		glUseProgram(drawShaderID);
		glBindVertexArray(vaoID);

		glUniformMatrix4fv(1, 1, GL_FALSE, (const GLfloat*)&Input::cam.C.x.x);
		glUniformMatrix4fv(5, 1, GL_FALSE, (const GLfloat*)&Input::cam.P.x.x);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

};

const float TerrainTexture::squareCoords[8] = {
		-100.0f, -100.0f,
		100.0f, -100.0f,
		-100.0f, 100.0f,
		100.0f, 100.0f
};

#endif