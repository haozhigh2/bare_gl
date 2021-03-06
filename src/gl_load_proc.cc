
#include "gl_load_proc.h"

GL_DEFINE_FUNCTION(wglCreateContextAttribsARB);
GL_DEFINE_FUNCTION(glCreateProgram);
GL_DEFINE_FUNCTION(glLinkProgram);
GL_DEFINE_FUNCTION(glUseProgram);
GL_DEFINE_FUNCTION(glDeleteProgram);
GL_DEFINE_FUNCTION(glCreateShader);
GL_DEFINE_FUNCTION(glShaderSource);
GL_DEFINE_FUNCTION(glCompileShader);
GL_DEFINE_FUNCTION(glAttachShader);
GL_DEFINE_FUNCTION(glDeleteShader);
GL_DEFINE_FUNCTION(glGenBuffers);
GL_DEFINE_FUNCTION(glIsBuffer);
GL_DEFINE_FUNCTION(glBindBuffer);
GL_DEFINE_FUNCTION(glBufferData);
GL_DEFINE_FUNCTION(glDeleteBuffers);
GL_DEFINE_FUNCTION(glGenQueries);
GL_DEFINE_FUNCTION(glBeginQuery);
GL_DEFINE_FUNCTION(glEndQuery);
GL_DEFINE_FUNCTION(glGetQueryObjectuiv);
GL_DEFINE_FUNCTION(glVertexAttribPointer);
GL_DEFINE_FUNCTION(glEnableVertexAttribArray);
GL_DEFINE_FUNCTION(glGetShaderiv);
GL_DEFINE_FUNCTION(glGetShaderInfoLog);
GL_DEFINE_FUNCTION(glGetProgramiv);
GL_DEFINE_FUNCTION(glGetProgramInfoLog);
GL_DEFINE_FUNCTION(glTransformFeedbackVaryings);
GL_DEFINE_FUNCTION(glGetTransformFeedbackVarying);
GL_DEFINE_FUNCTION(glBeginTransformFeedback);
GL_DEFINE_FUNCTION(glEndTransformFeedback);
GL_DEFINE_FUNCTION(glBindBufferBase);
GL_DEFINE_FUNCTION(glMapBuffer);
GL_DEFINE_FUNCTION(glGetShaderSource);
GL_DEFINE_FUNCTION(glGetAttachedShaders);
GL_DEFINE_FUNCTION(glIsProgram);
GL_DEFINE_FUNCTION(glGetUniformLocation);
GL_DEFINE_FUNCTION(glUniform1f);
GL_DEFINE_FUNCTION(glUniform2f);
GL_DEFINE_FUNCTION(glUniform3f);
GL_DEFINE_FUNCTION(glUniform4f);
GL_DEFINE_FUNCTION(glUniform1fv);
GL_DEFINE_FUNCTION(glUniform2fv);
GL_DEFINE_FUNCTION(glUniform3fv);
GL_DEFINE_FUNCTION(glUniform4fv);
GL_DEFINE_FUNCTION(glUniformMatrix2fv);
GL_DEFINE_FUNCTION(glUniformMatrix3fv);
GL_DEFINE_FUNCTION(glUniformMatrix4fv);
GL_DEFINE_FUNCTION(glGetStringi);
GL_DEFINE_FUNCTION(glGetBufferSubData);
GL_DEFINE_FUNCTION(glGetVertexAttribfv);
GL_DEFINE_FUNCTION(glGetVertexAttribiv);
GL_DEFINE_FUNCTION(glGenVertexArrays);
GL_DEFINE_FUNCTION(glBindVertexArray);
GL_DEFINE_FUNCTION(glIsVertexArray);
GL_DEFINE_FUNCTION(glDeleteVertexArrays);
GL_DEFINE_FUNCTION(glUniform1iv);
GL_DEFINE_FUNCTION(glUniform2iv);
GL_DEFINE_FUNCTION(glUniform3iv);
GL_DEFINE_FUNCTION(glUniform4iv);
GL_DEFINE_FUNCTION(glUniform1i);
GL_DEFINE_FUNCTION(glUniform2i);
GL_DEFINE_FUNCTION(glUniform3i);
GL_DEFINE_FUNCTION(glUniform4i);
GL_DEFINE_FUNCTION(glActiveTexture);

void gl_load_proc() {
    GL_GET_FUNCTION_ADDRESS(wglCreateContextAttribsARB);
    GL_GET_FUNCTION_ADDRESS(glCreateProgram);
    GL_GET_FUNCTION_ADDRESS(glLinkProgram);
	GL_GET_FUNCTION_ADDRESS(glUseProgram);
	GL_GET_FUNCTION_ADDRESS(glDeleteProgram);
	GL_GET_FUNCTION_ADDRESS(glCreateShader);
	GL_GET_FUNCTION_ADDRESS(glShaderSource);
	GL_GET_FUNCTION_ADDRESS(glCompileShader);
	GL_GET_FUNCTION_ADDRESS(glAttachShader);
	GL_GET_FUNCTION_ADDRESS(glDeleteShader);
	GL_GET_FUNCTION_ADDRESS(glGenBuffers);
    GL_GET_FUNCTION_ADDRESS(glIsBuffer);
	GL_GET_FUNCTION_ADDRESS(glBindBuffer);
	GL_GET_FUNCTION_ADDRESS(glBufferData);
	GL_GET_FUNCTION_ADDRESS(glDeleteBuffers);
	GL_GET_FUNCTION_ADDRESS(glGenQueries);
	GL_GET_FUNCTION_ADDRESS(glBeginQuery);
	GL_GET_FUNCTION_ADDRESS(glEndQuery);
	GL_GET_FUNCTION_ADDRESS(glGetQueryObjectuiv);
	GL_GET_FUNCTION_ADDRESS(glVertexAttribPointer);
	GL_GET_FUNCTION_ADDRESS(glEnableVertexAttribArray);
    GL_GET_FUNCTION_ADDRESS(glGetShaderiv);
    GL_GET_FUNCTION_ADDRESS(glGetShaderInfoLog);
    GL_GET_FUNCTION_ADDRESS(glGetProgramiv);
    GL_GET_FUNCTION_ADDRESS(glGetProgramInfoLog);
    GL_GET_FUNCTION_ADDRESS(glTransformFeedbackVaryings);
    GL_GET_FUNCTION_ADDRESS(glGetTransformFeedbackVarying);
    GL_GET_FUNCTION_ADDRESS(glBeginTransformFeedback);
    GL_GET_FUNCTION_ADDRESS(glEndTransformFeedback);
    GL_GET_FUNCTION_ADDRESS(glBindBufferBase);
    GL_GET_FUNCTION_ADDRESS(glMapBuffer);
	GL_GET_FUNCTION_ADDRESS(glGetShaderSource);
	GL_GET_FUNCTION_ADDRESS(glGetAttachedShaders);
	GL_GET_FUNCTION_ADDRESS(glIsProgram);
    GL_GET_FUNCTION_ADDRESS(glGetUniformLocation);
    GL_GET_FUNCTION_ADDRESS(glUniform1f);
    GL_GET_FUNCTION_ADDRESS(glUniform2f);
    GL_GET_FUNCTION_ADDRESS(glUniform3f);
    GL_GET_FUNCTION_ADDRESS(glUniform4f);
    GL_GET_FUNCTION_ADDRESS(glUniform1fv);
    GL_GET_FUNCTION_ADDRESS(glUniform2fv);
    GL_GET_FUNCTION_ADDRESS(glUniform3fv);
    GL_GET_FUNCTION_ADDRESS(glUniform4fv);
    GL_GET_FUNCTION_ADDRESS(glUniformMatrix2fv);
    GL_GET_FUNCTION_ADDRESS(glUniformMatrix3fv);
    GL_GET_FUNCTION_ADDRESS(glUniformMatrix4fv);
    GL_GET_FUNCTION_ADDRESS(glGetStringi);
    GL_GET_FUNCTION_ADDRESS(glGetBufferSubData);
    GL_GET_FUNCTION_ADDRESS(glGetVertexAttribfv);
    GL_GET_FUNCTION_ADDRESS(glGetVertexAttribiv);
    GL_GET_FUNCTION_ADDRESS(glGenVertexArrays);
    GL_GET_FUNCTION_ADDRESS(glIsVertexArray);
    GL_GET_FUNCTION_ADDRESS(glBindVertexArray);
    GL_GET_FUNCTION_ADDRESS(glDeleteVertexArrays);
    GL_GET_FUNCTION_ADDRESS(glUniform1iv);
    GL_GET_FUNCTION_ADDRESS(glUniform2iv);
    GL_GET_FUNCTION_ADDRESS(glUniform3iv);
    GL_GET_FUNCTION_ADDRESS(glUniform4iv);
    GL_GET_FUNCTION_ADDRESS(glUniform1i);
    GL_GET_FUNCTION_ADDRESS(glUniform2i);
    GL_GET_FUNCTION_ADDRESS(glUniform3i);
    GL_GET_FUNCTION_ADDRESS(glUniform4i);
    GL_GET_FUNCTION_ADDRESS(glActiveTexture);
}
