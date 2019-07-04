
#include "gl_load_proc.h"

glCreateProgramType glCreateProgram;
glLinkProgramType glLinkProgram;
glUseProgramType glUseProgram;
glDeleteProgramType glDeleteProgram;
glCreateShaderType glCreateShader;
glShaderSourceType glShaderSource;
glCompileShaderType glCompileShader;
glAttachShaderType glAttachShader;
glDeleteShaderType glDeleteShader;
glGenBuffersType glGenBuffers;
glBindBufferType glBindBuffer;
glBufferDataType glBufferData;
glDeleteBuffersType glDeleteBuffers;
//glDrawArraysType glDrawArrays;
glGenQueriesType glGenQueries;
glBeginQueryType glBeginQuery;
glEndQueryType glEndQuery;
glGetQueryObjectuivType glGetQueryObjectuiv;
//glDisableType glDisable;
//glEnableType glEnable;
glVertexAttribPointerType glVertexAttribPointer;

void gl_load_proc() {
	glCreateProgram = (glCreateProgramType)wglGetProcAddress("glCreateProgram");
	glLinkProgram = (glLinkProgramType)wglGetProcAddress("glLinkProgram");
	glUseProgram = (glUseProgramType)wglGetProcAddress("glUseProgram");
	glDeleteProgram = (glDeleteProgramType)wglGetProcAddress("glDeleteProgram");
	glCreateShader = (glCreateShaderType)wglGetProcAddress("glCreateShader");
	glShaderSource = (glShaderSourceType)wglGetProcAddress("glShaderSource");
	glCompileShader = (glCompileShaderType)wglGetProcAddress("glCompileShader");
	glAttachShader = (glAttachShaderType)wglGetProcAddress("glAttachShader");
	glDeleteShader = (glDeleteShaderType)wglGetProcAddress("glDeleteShader");
	glGenBuffers = (glGenBuffersType)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (glBindBufferType)wglGetProcAddress("glBindBuffer");
	glBufferData = (glBufferDataType)wglGetProcAddress("glBufferData");
	glDeleteBuffers = (glDeleteBuffersType)wglGetProcAddress("glDeleteBuffers");
	//glDrawArrays = (glDrawArraysType)wglGetProcAddress("glDrawArrays");
	glGenQueries = (glGenQueriesType)wglGetProcAddress("glGenQueries");
	glBeginQuery = (glBeginQueryType)wglGetProcAddress("glBeginQuery");
	glEndQuery = (glEndQueryType)wglGetProcAddress("glEndQuery");
	glGetQueryObjectuiv = (glGetQueryObjectuivType)wglGetProcAddress("glGetQueryObjectuiv");
	//glDisable = (glDisableType)wglGetProcAddress("glDisable");
	//glEnable = (glEnableType)wglGetProcAddress("glEnable");
	glVertexAttribPointer = (glVertexAttribPointerType)wglGetProcAddress("glVertexAttribPointer");
}
