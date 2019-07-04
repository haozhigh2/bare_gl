#pragma once

#include "GL/glcorearb.h"

void gl_load_proc();

extern "C" {
	typedef GLuint(__stdcall *glCreateProgramType)();
	extern glCreateProgramType glCreateProgram;

	typedef void (__stdcall *glLinkProgramType)(GLuint);
	extern glLinkProgramType glLinkProgram;

	typedef void (__stdcall *glUseProgramType)(GLuint);
	extern glUseProgramType glUseProgram;

	typedef void (__stdcall *glDeleteProgramType)(GLuint);
	extern glDeleteProgramType glDeleteProgram;

	typedef GLuint(__stdcall *glCreateShaderType)(GLenum);
	extern glCreateShaderType glCreateShader;

	typedef void (__stdcall *glShaderSourceType)(GLuint, GLsizei, const GLchar* const*, const GLint*);
	extern glShaderSourceType glShaderSource;

	typedef void (__stdcall *glCompileShaderType)(GLuint);
	extern glCompileShaderType glCompileShader;

	typedef void (__stdcall *glAttachShaderType)(GLuint, GLuint);
	extern glAttachShaderType glAttachShader;

	typedef void (__stdcall *glDeleteShaderType)(GLuint);
	extern glDeleteShaderType glDeleteShader;

	typedef void (__stdcall *glGenBuffersType)(GLsizei, GLuint*);
	extern glGenBuffersType glGenBuffers;

	typedef void (__stdcall *glBindBufferType)(GLenum, GLuint);
	extern glBindBufferType glBindBuffer;

	typedef void (__stdcall *glBufferDataType)(GLenum, GLsizeiptr, const void*, GLenum);
	extern glBufferDataType glBufferData;

	typedef void (__stdcall *glDeleteBuffersType)(GLsizei, const GLuint*);
	extern glDeleteBuffersType glDeleteBuffers;

	//typedef void (__stdcall *glDrawArraysType)(GLenum, GLint, GLsizei);
	//extern glDrawArraysType glDrawArrays;

	typedef void (__stdcall *glGenQueriesType)(GLsizei, GLuint *);
	extern glGenQueriesType glGenQueries;

	typedef void (__stdcall *glBeginQueryType)(GLenum, GLuint);
	extern glBeginQueryType glBeginQuery;

	typedef void (__stdcall *glEndQueryType)(GLenum);
	extern glEndQueryType glEndQuery;

	typedef void (__stdcall *glGetQueryObjectuivType)(GLuint, GLenum, GLuint *);
	extern glGetQueryObjectuivType glGetQueryObjectuiv;

	typedef void (_stdcall *glVertexAttribPointerType)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
	extern glVertexAttribPointerType glVertexAttribPointer;

	//typedef void (__stdcall *glDisableType)(GLenum);
	//extern glDisableType glDisable;

	//typedef void (__stdcall *glEnableType)(GLenum);
	//extern glEnableType glEnable;
}
