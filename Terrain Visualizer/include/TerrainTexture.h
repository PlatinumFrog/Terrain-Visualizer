#ifndef TERRAIN_TEXTURE
#define TERRAIN_TEXTURE

#include <SDL.h>
#include "SDL_image.h"
#ifdef _DEBUG
#include "../libraries/gladDebug/include/glad.h"
#else
#include "../libraries/gladRelease/include/glad.h"
#endif
#include <SDL_opengl.h>
#include "Input.h"
#include "Shader.h"

constexpr float gridSize = 1000.0f;
constexpr uint32_t nTiles = 64u;
constexpr float tileMin = (float)(nTiles >> 1);
constexpr float tileMax = tileMin - 1.0f;
constexpr float tileSize = gridSize / (float)nTiles;
constexpr float texCoordSize = 1.0f / (float)nTiles;
constexpr uint32_t vertSize = 4u;
constexpr uint32_t vertsPerTile = 4u;
constexpr uint32_t primitiveSize = vertSize * vertsPerTile;
constexpr uint32_t gridBufferSize = primitiveSize * nTiles * nTiles;
constexpr uint32_t nPrimitives = vertsPerTile * nTiles * nTiles;



class TerrainTexture {
	GLuint vboID, vaoID, heightMapTexID;

	const GLuint nShaders = 2;
	GLuint shaderList[2];
	GLuint currentShader;

	bool shaderLswitch;
	bool shaderRswitch;
	

public:
	TerrainTexture():
		vboID(0),
		vaoID(0),
		heightMapTexID(0),
		currentShader(0),
		shaderLswitch(false),
		shaderRswitch(false)
		
	{
		shaderList[0] = Shaders::compileShader(
			"normals.vert",
			"normals.tesc",
			"normals.tese",
			"normals.frag"
		);
		shaderList[1] = Shaders::compileShader(
			"wireframe.vert",
			"wireframe.tesc",
			"wireframe.tese",
			"wireframe.geom",
			"wireframe.frag"
		);

		GLfloat *squareCoords = new GLfloat[gridBufferSize];
		for (uint32_t y = 0; y < nTiles; y++) {
			for (uint32_t x = 0; x < nTiles; x++) {

				uint32_t i = primitiveSize * (x + (nTiles * y));

				float x1 = ((float)(x) - tileMin) * tileSize, x2 = ((float)(x) - tileMax) * tileSize,
					  y1 = ((float)(y) - tileMin) * tileSize, y2 = ((float)(y) - tileMax) * tileSize,
					  texCoordsX1 = (float)(x) * texCoordSize, texCoordsX2 = ((float)(x) + 1.0f) * texCoordSize,
					  texCoordsY1 = (float)(y) * texCoordSize, texCoordsY2 = ((float)(y) + 1.0f) * texCoordSize;

				squareCoords[i] = x1;
				squareCoords[i + 1] = y1;
				squareCoords[i + 2] = texCoordsX1;
				squareCoords[i + 3] = texCoordsY1;

				squareCoords[i + 4] = x2;
				squareCoords[i + 5] = y1;
				squareCoords[i + 6] = texCoordsX2;
				squareCoords[i + 7] = texCoordsY1;

				squareCoords[i + 8] = x1;
				squareCoords[i + 9] = y2;
				squareCoords[i + 10] = texCoordsX1;
				squareCoords[i + 11] = texCoordsY2;

				squareCoords[i + 12] = x2;
				squareCoords[i + 13] = y2;
				squareCoords[i + 14] = texCoordsX2;
				squareCoords[i + 15] = texCoordsY2;

				
			}
		}

		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareCoords), squareCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glPatchParameteri(GL_PATCH_VERTICES, 4);
		delete squareCoords;
	};

	TerrainTexture(std::string heightMapFile):
		vboID(0),
		vaoID(0),
		heightMapTexID(0),
		currentShader(0),
		shaderLswitch(false),
		shaderRswitch(false)
	{
		shaderList[0] = Shaders::compileShader(
			"normals.vert",
			"normals.tesc",
			"normals.tese",
			"normals.frag"
		);
		shaderList[1] = Shaders::compileShader(
			"wireframe.vert",
			"wireframe.tesc",
			"wireframe.tese",
			"wireframe.geom",
			"wireframe.frag"
		);

		
		GLfloat squareCoords[gridBufferSize];
		for (uint32_t y = 0; y < nTiles; y++) {
			for (uint32_t x = 0; x < nTiles; x++) {

				uint32_t i = primitiveSize * (x + (nTiles * y));

				float x1 = ((float)(x)-tileMin) * tileSize, x2 = ((float)(x)-tileMax) * tileSize,
					y1 = ((float)(y)-tileMin) * tileSize, y2 = ((float)(y)-tileMax) * tileSize,
					texCoordsX1 = (float)(x)*texCoordSize, texCoordsX2 = ((float)(x)+1.0f) * texCoordSize,
					texCoordsY1 = (float)(y)*texCoordSize, texCoordsY2 = ((float)(y)+1.0f) * texCoordSize;

				squareCoords[i] = x1;
				squareCoords[i + 1] = y1;
				squareCoords[i + 2] = texCoordsX1;
				squareCoords[i + 3] = texCoordsY1;

				squareCoords[i + 4] = x2;
				squareCoords[i + 5] = y1;
				squareCoords[i + 6] = texCoordsX2;
				squareCoords[i + 7] = texCoordsY1;

				squareCoords[i + 8] = x1;
				squareCoords[i + 9] = y2;
				squareCoords[i + 10] = texCoordsX1;
				squareCoords[i + 11] = texCoordsY2;

				squareCoords[i + 12] = x2;
				squareCoords[i + 13] = y2;
				squareCoords[i + 14] = texCoordsX2;
				squareCoords[i + 15] = texCoordsY2;
			}
		}

		SDL_Surface* img = IMG_Load(heightMapFile.c_str());
		glGenTextures(1, &heightMapTexID);
		glBindTexture(GL_TEXTURE_2D, heightMapTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, img->w, img->h, 0, GL_RED, GL_UNSIGNED_BYTE, img->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SDL_FreeSurface(img);
		

		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareCoords), squareCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glPatchParameteri(GL_PATCH_VERTICES, 4);
	};

	~TerrainTexture() {
		glDeleteBuffers(1, &vboID);
		glDeleteVertexArrays(1, &vaoID);
		glDeleteProgram(shaderList[0]);
		glDeleteProgram(shaderList[1]);
	}
	void draw(float h) {

		if (Input::key(SDL_SCANCODE_COMMA) && !shaderLswitch) {
			if (currentShader > 0) currentShader--;
			shaderLswitch = true;
		} else if (!Input::key(SDL_SCANCODE_COMMA) && shaderLswitch) {
			shaderLswitch = false;
		}

		if (Input::key(SDL_SCANCODE_PERIOD) && !shaderRswitch) {

			if (currentShader < (nShaders - 1)) currentShader++;

			shaderRswitch = true;
		} else if (!Input::key(SDL_SCANCODE_PERIOD) && shaderRswitch) {
			shaderRswitch = false;
		}

		glUseProgram(shaderList[currentShader]);
		glBindVertexArray(vaoID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, heightMapTexID);

		glUniformMatrix4fv(1, 1, GL_FALSE, (const GLfloat*)&Input::cam.C.x.x);
		glUniformMatrix4fv(5, 1, GL_FALSE, (const GLfloat*)&Input::cam.P.x.x);
		glUniform1f(9, gridSize * 0.5f);
		glUniform1f(10, h);
		glDrawArrays(GL_PATCHES, 0, nPrimitives);
	}

};

#endif