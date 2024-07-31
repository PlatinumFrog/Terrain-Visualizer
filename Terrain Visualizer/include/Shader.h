#ifndef SHADER_COMPILERS
#define SHADER_COMPILERS

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#ifdef _DEBUG
#include "../libraries/gladDebug/include/glad.h"
#else
#include "../libraries/gladRelease/include/glad.h"
#endif
struct shader {
	std::map<std::string, std::string> files;
	/*	Tessellation Control
		Tessellation Evaluation
		Geometry                */
	uint8_t flags;
};

class Shaders {
	static std::map<GLuint, shader> shaders;
public:
	static GLuint compileShader(const std::string& vertexFileName, const std::string& fragmentFileName);
	static GLuint compileShader(const std::string& vertexFileName, const std::string& geometryFileName, const std::string& fragmentFileName);
	static GLuint compileShader(const std::string& vertexFileName, const std::string& tessellationControlFileName, const std::string& tessellationEvaluationFileName, const std::string& fragmentFileName);
	static GLuint compileShader(const std::string& vertexFileName, const std::string& tessellationControlFileName, const std::string& tessellationEvaluationFileName, const std::string& geometryFileName, const std::string& fragmentFileName);
	//static GLuint compileShader(const GLuint ID);
};

#endif