#pragma once

#include "lib/glad.h"
#include "auxiliary/util.h"
#include "auxiliary/errors.h"


#define PRIMITIVES_ERRCHECK

#ifdef PRIMITIVES_ERRCHECK
#define PRIM_CHECKERR(msg) { GLenum err; while ((err = glGetError ()) != GL_NO_ERROR) warnError (msg": 0x%x", err); }
#else
#define PRIM_CHECKERR(msg) ;
#endif


namespace gl {

	class Primitive {
	public:
		GLuint VAO, VBO, EBO;
		GLsizei indCount;
		GLenum drawMode;


		Primitive (GLenum VBO_usage, const GLfloat *vertices, GLsizeiptr vertSize,
		           const GLuint *indices, GLsizeiptr indSize, GLsizei indCount) {
			this->indCount = indCount;
			glGenVertexArrays (1, &VAO);
			glBindVertexArray (VAO);
			glGenBuffers (1, &VBO);
			glGenBuffers (1, &EBO);
			glBindBuffer (GL_ARRAY_BUFFER, VBO);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData (GL_ARRAY_BUFFER, vertSize, vertices, VBO_usage);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, indSize, indices, GL_STATIC_DRAW);
			PRIM_CHECKERR ("Error while creating a primitive");
		}


		void setAttributes (GLuint index, GLint size, int stride, int pointer) {
			glBindBuffer (GL_ARRAY_BUFFER, VBO);
			glVertexAttribPointer (index, size, GL_FLOAT, GL_FALSE, gl::sizef (stride), gl::psizef (pointer));
			glEnableVertexAttribArray (index);
			PRIM_CHECKERR ("Error setting attributes to a primitive");
		}


		void bind () {
			glBindVertexArray (VAO);
			PRIM_CHECKERR ("Error while binding a primitive");
		}


		void draw () {
			glBindVertexArray (VAO);
			glDrawElements (drawMode, indCount, GL_UNSIGNED_INT, 0);
			PRIM_CHECKERR ("Error while drawing a primitive");
		}
	};


	class Rect : public Primitive {
		const static GLuint indices[4];
	public:
		Rect (GLenum VBO_usage, const GLfloat *vertices, GLsizeiptr vertSize)
				: Primitive (VBO_usage, vertices, vertSize, indices, sizeof (indices), 4) {
			drawMode = GL_TRIANGLE_FAN;
		}
	};


	class Hex : public Primitive {
		const static GLuint indices[6];
	public:
		Hex (GLenum VBO_usage, const GLfloat *vertices, GLsizeiptr vertSize)
				: Primitive (VBO_usage, vertices, vertSize, indices, sizeof (indices), 6) {
			drawMode = GL_TRIANGLE_FAN;
		}
	};

}
