#ifndef SHADER_COMPILERS
#define SHADER_COMPILERS

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#ifdef _DEBUG
#include "../gladDebug/include/glad.h"
#else
#include "../gladRelease/include/glad.h"
#endif
struct shader {
	bool geom;
	std::string vertFile, vertString;
	std::string geomFile, geomString;
	std::string fragFile, fragString;
};

class Shaders {
	static std::map<GLuint, shader> shaders;
public:
	static GLuint compileShader(const std::string& vertexFileName, const std::string& fragmentFileName);
	static GLuint compileShader(const std::string& vertexFileName, const std::string& geometryFileName, const std::string& fragmentFileName);
	static GLuint compileShader(const GLuint ID);
};

#endif