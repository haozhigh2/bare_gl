#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include "gl_load_proc.h"

class UniformBase {
public:
    UniformBase(const string& name) : _name(name) { }
    virtual int Set() const = 0;
    GLint GetUniformLocation() const {
        GLint program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &program);
        if (program <= 0)
            return -1;
        else
            return glGetUniformLocation(program, _name.c_str());
    }

protected:
    string _name;
};

class Uniform4fv : public UniformBase {
public:
    Uniform4fv(const string& name, const GLfloat* data): UniformBase(name) {
        for (int i = 0; i < 16; i++)
            _data[i] = data[i];
    }

    int Set() const {
        GLint location = GetUniformLocation();
        if (location >= 0)
            glUniformMatrix4fv(location, 1, GL_TRUE, _data);
    }

private:
    GLfloat _data[16];
};

class Uniform1f : public UniformBase {
public:
    Uniform1f(const string& name, GLfloat data): UniformBase(name), _data(data) { }

    int Set() const {
        GLint location = GetUniformLocation();
        if (location >= 0)
            glUniform1f(location, _data);
    }

private:
    GLfloat _data;
};

class Uniform4f : public UniformBase {
public:
    Uniform4f(const string& name, GLfloat data0, GLfloat data1, GLfloat data2, GLfloat data3): UniformBase(name) {
        _data[0] = data0;
        _data[1] = data1;
        _data[2] = data2;
        _data[3] = data3;
    }

    int Set() const {
        GLint location = GetUniformLocation();
        if (location >= 0)
            glUniform4f(location, _data[0], _data[1], _data[2], _data[3]);
    }

private:
    GLfloat _data[4];
};