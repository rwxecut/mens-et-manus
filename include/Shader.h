#pragma once

#include "lib/glad.h"
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "lib/glm/vec2.hpp"
#include "lib/glm/mat4x4.hpp"


class Shader {
	GLenum type;
	const static std::map<GLenum, const char *> typeStr;
	std::string name;

public:
	GLuint id;

	enum SourceType {
		fromString, fromFile
	};

	Shader (const std::string name, GLenum type, Shader::SourceType sourceType, const GLchar *source);
	~Shader ();
};


typedef std::vector<Shader *> ShaderList;


class ShaderProgram {
	std::string name;

	void init (const std::string name, const ShaderList &shaderList);

public:
	GLuint id;

	void use ();

	void setUniform (const GLchar *name, GLint value);
	void setUniform (const GLchar *name, GLfloat value);
	void setUniform (const GLchar *name, const glm::vec2 &value);
	void setUniform (const GLchar *name, const glm::mat4 &value);

	ShaderProgram (const std::string name, const ShaderList &shaderList);
	ShaderProgram (const std::string name, Shader::SourceType vertSourceType, const GLchar *vertSource,
	               Shader::SourceType fragSourceType, const GLchar *fragSource);
	~ShaderProgram ();
};

using ShaderProgramPtr = std::unique_ptr<ShaderProgram>;
