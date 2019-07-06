#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include "gl_load_proc.h"
#include "program.hpp"

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

            GLint status;
            glGetShaderiv(shader_ids.back(), GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE) {
                throw - 1;
                string log;
                GLint log_length;
                glGetShaderiv(shader_ids.back(), GL_INFO_LOG_LENGTH, &log_length);
                log.reserve(log_length);
                glGetShaderInfoLog(shader_ids.back(), log_length, NULL, &log[0]);
            }

			glAttachShader(_program, shader_ids.back());
		}

        //auto varying = string("gl_Position").c_str();
        const char* varying = "gl_Position";
        glTransformFeedbackVaryings(_program, 1, &varying, GL_INTERLEAVED_ATTRIBS);

		glLinkProgram(_program);

        GLint status;
        glGetProgramiv(_program, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            //throw - 1;
            string log;
            GLint log_length;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_length);
            log.reserve(log_length);
            glGetProgramInfoLog(_program, log_length, NULL, &log[0]);
        }

		//for (auto& it : shader_ids)
		//	glDeleteShader(it);
	}

	void Use() {
        if (_program != NULL) {
            GLenum err;
            err = glGetError();

    GLint int_value;
    glGetIntegerv(GL_CURRENT_PROGRAM, &int_value);

			glUseProgram(_program);

    glGetIntegerv(GL_CURRENT_PROGRAM, &int_value);

            err = glGetError();
        }
	}

	~Program() {
		glDeleteProgram(_program);
	}

private:
	GLuint _program;
};