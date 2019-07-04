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
			glAttachShader(_program, shader_ids.back());
		}

		glLinkProgram(_program);
		for (auto& it : shader_ids)
			glDeleteShader(it);
	}

	void Use() {
		if (_program != NULL)
			glUseProgram(_program);
	}

	~Program() {
		glDeleteProgram(_program);
	}

private:
	GLuint _program;
};