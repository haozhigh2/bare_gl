
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
glGenQueriesType glGenQueries;
glBeginQueryType glBeginQuery;
glEndQueryType glEndQuery;
glGetQueryObjectuivType glGetQueryObjectuiv;
glVertexAttribPointerType glVertexAttribPointer;
glGetShaderivType glGetShaderiv;
glGetShaderInfoLogType glGetShaderInfoLog;
glGetProgramivType glGetProgramiv;
glGetProgramInfoLogType glGetProgramInfoLog;
glTransformFeedbackVaryingsType glTransformFeedbackVaryings;
glGetTransformFeedbackVaryingType glGetTransformFeedbackVarying;
glBeginTransformFeedbackType glBeginTransformFeedback;
glEndTransformFeedbackType glEndTransformFeedback;
glBindBufferBaseType glBindBufferBase;
glMapBufferType glMapBuffer;

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
	glGenQueries = (glGenQueriesType)wglGetProcAddress("glGenQueries");
	glBeginQuery = (glBeginQueryType)wglGetProcAddress("glBeginQuery");
	glEndQuery = (glEndQueryType)wglGetProcAddress("glEndQuery");
	glGetQueryObjectuiv = (glGetQueryObjectuivType)wglGetProcAddress("glGetQueryObjectuiv");
	glVertexAttribPointer = (glVertexAttribPointerType)wglGetProcAddress("glVertexAttribPointer");
    glGetShaderiv = (glGetShaderivType)wglGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (glGetShaderInfoLogType)wglGetProcAddress("glGetShaderInfoLog");
    glGetProgramiv = (glGetProgramivType)wglGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (glGetProgramInfoLogType)wglGetProcAddress("glGetProgramInfoLog");
    glTransformFeedbackVaryings = (glTransformFeedbackVaryingsType)wglGetProcAddress("glTransformFeedbackVaryings");
    glGetTransformFeedbackVarying = (glGetTransformFeedbackVaryingType)wglGetProcAddress("glGetTransformFeedbackVarying");
    glBeginTransformFeedback = (glBeginTransformFeedbackType)wglGetProcAddress("glBeginTransformFeedback");
    glEndTransformFeedback = (glEndTransformFeedbackType)wglGetProcAddress("glEndTransformFeedback");
    glBindBufferBase = (glBindBufferBaseType)wglGetProcAddress("glBindBufferBase");
    glMapBuffer = (glMapBufferType)wglGetProcAddress("glMapBuffer");
}
