#include "client/Shader.h"
#include "lib/glm/gtc/type_ptr.hpp"
#include "auxiliary/errors.h"
#include "auxiliary/util.h"

const std::map<GLenum, const char *> Shader::typeStr = {
		{GL_VERTEX_SHADER,   "Vertex"},
		{GL_FRAGMENT_SHADER, "Fragment"}
};


Shader::Shader (const std::string& name, GLenum type, Shader::SourceType sourceType,
                const GLchar *source) : name(name), type(type) {
	GLint success = 0;
	std::string log;

	// Load shader
	id = glCreateShader (type);
	if (sourceType == fromString) {
		glShaderSource (id, 1, &source, NULL);
		glCompileShader (id);
	} else {
		bool loadSuccess = false;
		std::string loaded = loadFileToString (source, loadSuccess);
		if (!loadSuccess) {
			warnError ("%s shader \"%s\" error: failed to open %s file", typeStr.at (type), name.c_str (), source);
			return;
		}
		const GLchar *loadedStr = loaded.c_str ();
		glShaderSource (id, 1, &loadedStr, NULL);
		glCompileShader (id);
	}

	// Check compile status
	glGetShaderiv (id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logSize = 0;
		glGetShaderiv (id, GL_INFO_LOG_LENGTH, &logSize);
		log.resize (logSize);
		glGetShaderInfoLog (id, logSize, NULL, &log[0]);
		warnError ("%s shader \"%s\" error: %s", typeStr.at (type), name.c_str (), log.c_str ());
	} else
		logger.write ("%s shader \"%s\" compiled", typeStr.at (type), name.c_str ());
}


Shader::~Shader () {
	glDeleteShader (id);
}


void ShaderProgram::init (const ShaderList &shaderList) {
	GLint success = 0;
	std::string log;

	// Link program
	id = glCreateProgram ();
	for (auto shader : shaderList)
		glAttachShader (id, shader->id);
	glLinkProgram (id);

	// Check link status
	glGetProgramiv (id, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logSize = 0;
		glGetProgramiv (id, GL_INFO_LOG_LENGTH, &logSize);
		log.resize (logSize);
		glGetProgramInfoLog (id, logSize, NULL, &log[0]);
		warnError ("Shader program \"%s\" error: %s", name.c_str (), log.c_str ());
	} else
		logger.write ("Shader program \"%s\" linked", name.c_str ());
}


ShaderProgram::ShaderProgram (const std::string& name, const ShaderList &shaderList) : name(name) {
	init (shaderList);
}


ShaderProgram::ShaderProgram (const std::string& name, Shader::SourceType vertSourceType, const GLchar *vertSource,
                              Shader::SourceType fragSourceType, const GLchar *fragSource) : name(name) {
	Shader vertShader (name, GL_VERTEX_SHADER, vertSourceType, vertSource);
	Shader fragShader (name, GL_FRAGMENT_SHADER, fragSourceType, fragSource);
	init ({&vertShader, &fragShader});
}


ShaderProgram::~ShaderProgram () {
	glDeleteProgram (id);
}


void ShaderProgram::use () {
	glUseProgram (id);
}


void ShaderProgram::setUniform (const GLchar *name, GLint value) {
	GLint loc = glGetUniformLocation (id, name);
	glUniform1i (loc, value);
}


void ShaderProgram::setUniform (const GLchar *name, GLfloat value) {
	GLint loc = glGetUniformLocation (id, name);
	glUniform1f (loc, value);
}


void ShaderProgram::setUniform (const GLchar *name, const glm::vec2 &value) {
	GLint loc = glGetUniformLocation (id, name);
	glUniform2fv (loc, 1, glm::value_ptr (value));
}


void ShaderProgram::setUniform (const GLchar *name, const glm::mat4 &value) {
	GLint loc = glGetUniformLocation (id, name);
	glUniformMatrix4fv (loc, 1, GL_FALSE, glm::value_ptr (value));
}
