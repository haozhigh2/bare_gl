#pragma once

#include "GL/glcorearb.h"

void gl_load_proc();

#define GL_DECLARE_FUNCTION(FUNC) extern FUNC##Type FUNC
#define GL_DEFINE_FUNCTION(FUNC) FUNC##Type FUNC
#define GL_GET_FUNCTION_ADDRESS(FUNC) FUNC = (FUNC##Type)wglGetProcAddress(#FUNC)

extern "C" {
	typedef GLuint(__stdcall *glCreateProgramType)();
    GL_DECLARE_FUNCTION(glCreateProgram);

	typedef void (__stdcall *glLinkProgramType)(GLuint);
	GL_DECLARE_FUNCTION(glLinkProgram);

	typedef void (__stdcall *glUseProgramType)(GLuint);
	GL_DECLARE_FUNCTION(glUseProgram);

	typedef void (__stdcall *glDeleteProgramType)(GLuint);
	GL_DECLARE_FUNCTION(glDeleteProgram);

	typedef GLuint(__stdcall *glCreateShaderType)(GLenum);
	GL_DECLARE_FUNCTION(glCreateShader);

	typedef void (__stdcall *glShaderSourceType)(GLuint, GLsizei, const GLchar* const*, const GLint*);
	GL_DECLARE_FUNCTION(glShaderSource);

	typedef void (__stdcall *glCompileShaderType)(GLuint);
	GL_DECLARE_FUNCTION(glCompileShader);

	typedef void (__stdcall *glAttachShaderType)(GLuint, GLuint);
	GL_DECLARE_FUNCTION(glAttachShader);

	typedef void (__stdcall *glDeleteShaderType)(GLuint);
	GL_DECLARE_FUNCTION(glDeleteShader);

	typedef void (__stdcall *glGenBuffersType)(GLsizei, GLuint*);
	GL_DECLARE_FUNCTION(glGenBuffers);

	typedef void (__stdcall *glBindBufferType)(GLenum, GLuint);
	GL_DECLARE_FUNCTION(glBindBuffer);

	typedef void (__stdcall *glBufferDataType)(GLenum, GLsizeiptr, const void*, GLenum);
	GL_DECLARE_FUNCTION(glBufferData);

	typedef void (__stdcall *glDeleteBuffersType)(GLsizei, const GLuint*);
	GL_DECLARE_FUNCTION(glDeleteBuffers);

	typedef void (__stdcall *glGenQueriesType)(GLsizei, GLuint *);
	GL_DECLARE_FUNCTION(glGenQueries);

	typedef void (__stdcall *glBeginQueryType)(GLenum, GLuint);
	GL_DECLARE_FUNCTION(glBeginQuery);

	typedef void (__stdcall *glEndQueryType)(GLenum);
	GL_DECLARE_FUNCTION(glEndQuery);

	typedef void (__stdcall *glGetQueryObjectuivType)(GLuint, GLenum, GLuint *);
	GL_DECLARE_FUNCTION(glGetQueryObjectuiv);

	typedef void (_stdcall *glVertexAttribPointerType)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
	GL_DECLARE_FUNCTION(glVertexAttribPointer);

	typedef void (_stdcall *glEnableVertexAttribArrayType)(GLuint);
	GL_DECLARE_FUNCTION(glEnableVertexAttribArray);

    typedef void (_stdcall *glGetShaderivType)(GLuint, GLenum, GLint *);
    GL_DECLARE_FUNCTION(glGetShaderiv);

    typedef void (_stdcall *glGetShaderInfoLogType)(GLuint, GLsizei, GLsizei *, GLchar *);
    GL_DECLARE_FUNCTION(glGetShaderInfoLog);

    typedef void (_stdcall *glGetProgramivType)(GLuint, GLenum, GLint *);
    GL_DECLARE_FUNCTION(glGetProgramiv);

    typedef void (_stdcall *glGetProgramInfoLogType)(GLuint, GLsizei, GLsizei *, GLchar *);
    GL_DECLARE_FUNCTION(glGetProgramInfoLog);

    typedef void (_stdcall *glTransformFeedbackVaryingsType)(GLuint, GLsizei, const GLchar *const*, GLenum);
    GL_DECLARE_FUNCTION(glTransformFeedbackVaryings);

    typedef void (_stdcall *glGetTransformFeedbackVaryingType)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *size, GLenum *, GLchar *);
    GL_DECLARE_FUNCTION(glGetTransformFeedbackVarying);

    typedef void (_stdcall *glBeginTransformFeedbackType)(GLenum);
    GL_DECLARE_FUNCTION(glBeginTransformFeedback);

    typedef void (_stdcall *glEndTransformFeedbackType)(void);
    GL_DECLARE_FUNCTION(glEndTransformFeedback);

    typedef void (_stdcall *glBindBufferBaseType)(GLenum, GLuint, GLuint);
    GL_DECLARE_FUNCTION(glBindBufferBase);

    typedef void* (_stdcall *glMapBufferType)(GLenum, GLenum);
    GL_DECLARE_FUNCTION(glMapBuffer);

	typedef void (_stdcall *glGetShaderSourceType)(GLuint, GLsizei, GLsizei *, GLchar *);
	GL_DECLARE_FUNCTION(glGetShaderSource);

	typedef void (_stdcall *glGetAttachedShadersType)(GLuint, GLsizei, GLsizei *, GLuint *);
	GL_DECLARE_FUNCTION(glGetAttachedShaders);

	typedef GLboolean (_stdcall *glIsProgramType)(GLuint);
	GL_DECLARE_FUNCTION(glIsProgram);

    typedef GLint (_stdcall *glGetUniformLocationType)(GLuint, const GLchar *);
    GL_DECLARE_FUNCTION(glGetUniformLocation);

    typedef void (_stdcall *glUniform1fType)(GLint, GLfloat);
    GL_DECLARE_FUNCTION(glUniform1f);

    typedef void (_stdcall *glUniform2fType)(GLint, GLfloat, GLfloat);
    GL_DECLARE_FUNCTION(glUniform2f);

    typedef void (_stdcall *glUniform3fType)(GLint, GLfloat, GLfloat, GLfloat);
    GL_DECLARE_FUNCTION(glUniform3f);

    typedef void (_stdcall *glUniform4fType)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
    GL_DECLARE_FUNCTION(glUniform4f);

    typedef void (_stdcall *glUniformMatrix2fvType)(GLint, GLsizei, GLboolean, const GLfloat *);
    GL_DECLARE_FUNCTION(glUniformMatrix2fv);

    typedef void (_stdcall *glUniformMatrix3fvType)(GLint, GLsizei, GLboolean, const GLfloat *);
    GL_DECLARE_FUNCTION(glUniformMatrix3fv);

    typedef void (_stdcall *glUniformMatrix4fvType)(GLint, GLsizei, GLboolean, const GLfloat *);
    GL_DECLARE_FUNCTION(glUniformMatrix4fv);

    typedef void (_stdcall *glGenTexturesType)(GLsizei, GLuint *);
    GL_DECLARE_FUNCTION(glGenTextures);

    typedef void (_stdcall *glBindTextureType)(GLenum target, GLuint texture);
    GL_DECLARE_FUNCTION(glBindTexture);

    typedef void (_stdcall *glTexImage2DType)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
    GL_DECLARE_FUNCTION(glTexImage2D);

    typedef void (_stdcall *glTexParameteriType)(GLenum, GLenum, GLint);
    GL_DECLARE_FUNCTION(glTexParameteri);
}
