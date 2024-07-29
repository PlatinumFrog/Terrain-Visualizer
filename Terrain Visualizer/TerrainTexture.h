#ifndef TERRAIN_TEXTURE
#define TERRAIN_TEXTURE

#include <SDL.h>
#ifdef _DEBUG
#include "gladDebug/include/glad.h"
#else
#include "gladRelease/include/glad.h"
#endif
#include <SDL_opengl.h>

#include "Input.h"

class TerrainTexture {
	static const float squareCoords[8];
	GLuint vboID, vaoID, heightMapTexID, shadowMapTexID, drawShaderID, shadowShaderID;
public:
	TerrainTexture() {
		
	};
	~TerrainTexture();

	void draw();

};

const float TerrainTexture::squareCoords[8] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
};

#endif