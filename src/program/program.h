#pragma once

#include <string>
#include <map>
#include <vector>
#include <cassert>
using namespace std;

#include <GL/GL.h>
#include <gl/GLU.h>
#include "gl_load_proc.h"
#include "tool/mat.h"

class Program {
public:
	Program() : _program(NULL) { }

	void LoadShaders(const map<GLenum, string>& shaders) {
		if (_program != NULL) {
			glDeleteProgram(_program);
			_program = NULL;
		}
		_program = glCreateProgram();

		vector<GLuint> shader_ids;
		for (auto& it : shaders) {
			shader_ids.push_back(glCreateShader(it.first));
			auto c_str = it.second.c_str();
			int length = static_cast<int>(it.second.length());
			glShaderSource(shader_ids.back(), 1, &c_str, &length);
			glCompileShader(shader_ids.back());

#ifdef DEBUG_SHADER
            GLint status;
            glGetShaderiv(shader_ids.back(), GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE) {
                string log;
                GLint log_length;
                glGetShaderiv(shader_ids.back(), GL_INFO_LOG_LENGTH, &log_length);
                log.reserve(log_length);
                glGetShaderInfoLog(shader_ids.back(), log_length, NULL, &log[0]);
            }
            glGetShaderiv(shader_ids.back(), GL_SHADER_TYPE, &status);
            glGetShaderiv(shader_ids.back(), GL_DELETE_STATUS, &status);
            glGetShaderiv(shader_ids.back(), GL_COMPILE_STATUS, &status);
            glGetShaderiv(shader_ids.back(), GL_SHADER_SOURCE_LENGTH, &status);
			if (status > 0) {
				char* c_str = new char[status];
				glGetShaderSource(shader_ids.back(), status, NULL, c_str);
				delete[] c_str;
			}
#endif

			glAttachShader(_program, shader_ids.back());
		}

		glLinkProgram(_program);

#ifdef DEBUG_SHADER
        GLint status;
        glGetProgramiv(_program, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            string log;
            GLint log_length;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);
            log.reserve(log_length);
            glGetProgramInfoLog(_program, log_length, NULL, &log[0]);
        }
		GLuint attached_shaders[3];
		glGetAttachedShaders(_program, 3, NULL, attached_shaders);
		GLboolean is_program = glIsProgram(_program);
		glGetProgramiv(_program, GL_DELETE_STATUS, &status);
		glGetProgramiv(_program, GL_LINK_STATUS, &status);
		glGetProgramiv(_program, GL_VALIDATE_STATUS, &status);
		glGetProgramiv(_program, GL_ATTACHED_SHADERS, &status);
		glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &status);
		glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &status);
		glGetProgramiv(_program, GL_PROGRAM_BINARY_LENGTH, &status);
#endif

		for (auto& it : shader_ids)
			glDeleteShader(it);
	}

	void Use() {
        if (_program != 0) {
#ifdef DEBUG_SHADER
            GLenum err;
            err = glGetError();

			GLboolean is_program = glIsProgram(_program);
            GLint status;
            glGetProgramiv(_program, GL_DELETE_STATUS, &status);
            glGetProgramiv(_program, GL_LINK_STATUS, &status);
            glGetProgramiv(_program, GL_VALIDATE_STATUS, &status);
            glGetProgramiv(_program, GL_ATTACHED_SHADERS, &status);
            glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &status);
            glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &status);
            glGetProgramiv(_program, GL_PROGRAM_BINARY_LENGTH, &status);

			GLint int_value;
			glGetIntegerv(GL_CURRENT_PROGRAM, &int_value);
#endif

			glUseProgram(_program);
        }
	}

    void SetUniformMatrix4fv(const string& name, const mat4& data)
    {
        this->Use();
        GLint location{glGetUniformLocation(_program, name.c_str())};
        assert(location >= 0);
        glUniformMatrix4fv(location, 1, GL_TRUE, data.Data());
    }

    void SetUniform4fv(const string& name, const vec4& data)
    {
        this->Use();
        GLint location{glGetUniformLocation(_program, name.c_str())};
        assert(location >= 0);
        glUniform4fv(location, 1, data.Data());
    }

    void SetUniform1f(const string& name, float data)
    {
        this->Use();
        GLint location{glGetUniformLocation(_program, name.c_str())};
        assert(location >= 0);
        glUniform1f(location, data);
    }

    void SetUniform1i(const string& name, int data)
    {
        this->Use();
        GLint location{glGetUniformLocation(_program, name.c_str())};
        assert(location >= 0);
        glUniform1i(location, data);
    }

	~Program() {
		glDeleteProgram(_program);
	}

private:
	GLuint _program;
};