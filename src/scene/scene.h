#pragma once

#include <string>
using namespace std;

#include <Windows.h>
//#include <GL/GL.h>
//#include <GL/GLU.h>
#include "GL/glcorearb.h"
#include "GL/glext.h"
#include "GL/wglext.h"
#include "gl_load_proc.h"
#include "program/program.h"
#include "viewer/viewer.h"

class SceneBase
{
public:
    SceneBase(){};
    ~SceneBase(){};

    virtual void Draw() = 0;
    virtual string Name() = 0;
    virtual void KeyDown(unsigned key) = 0;

    virtual void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height) { glViewport(x, y, width, height); }

protected:
};

class SceneHelloWorld : public SceneBase
{
public:
    SceneHelloWorld() : _buffer(0), _vao(0)
    {
        const string vertex_shader_str = R"(
            #version 330 core
            layout (location = 0) in vec3 pos;
            
            void main(void) {
                gl_Position = vec4(pos, 1.0);
            }
        )";
        const string fragment_shader_str = R"(
            #version 330 core
            out vec4 color;
            void main(void) {
                color = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )";
        map<GLenum, string> shaders;
        shaders[GL_VERTEX_SHADER] = vertex_shader_str;
        shaders[GL_FRAGMENT_SHADER] = fragment_shader_str;
        _program.LoadShaders(shaders);

        InitBuffers();
    }
    ~SceneHelloWorld()
    {
        if (glIsBuffer(_buffer))
        {
            glDeleteBuffers(1, &_buffer);
            _buffer = 0;
        }
        if (glIsVertexArray(_vao))
        {
            glDeleteVertexArrays(1, &_vao);
            _vao = 0;
        }
    }

    void Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        _program.Use();
        glBindVertexArray(_vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    string Name() { return "HelloWorld"; }

    void KeyDown(unsigned key) {}

private:
    void InitBuffers()
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        static GLfloat data[9]{
            0.0f, 1.0f, 0.5f,
            -1.0f, 0.0f, 0.5f,
            1.0f, -1.0f, 0.5f};
        glGenBuffers(1, &_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, _buffer);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    }

private:
    Program _program;
    GLuint _buffer;
    GLuint _vao;
};

class SceneBoard : public SceneBase
{
public:
    SceneBoard(): _buffer(0), _vao(0)
    {
        _viewer.SetLoc(vec3{0.0f, 0.0f, 1.7f});
        _viewer.SetFrustum(PI / 2.0f, 1.6f);
        _viewer.LookAt(vec3{0.0f, 1.0f, 0.0f});

        InitProgram();
        InitBuffers();

        _program.SetUniform4fv("COLOR", vec4({0.9f, 0.9f, 0.9f, 0.9f}));
        _program.SetUniformMatrix4fv("TRANSFORM_LOCAL2NDC", _viewer.GetMatWorld2NDC());
    }

    ~SceneBoard()
    {
        if (glIsBuffer(_buffer))
        {
            glDeleteBuffers(1, &_buffer);
            _buffer = 0;
        }
        if (glIsVertexArray(_vao))
        {
            glDeleteVertexArrays(1, &_vao);
            _vao = 0;
        }
    }

    void Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        _program.Use();
        glBindVertexArray(_vao);

        glDrawArrays(GL_LINES, 0, 201 * 2 * 2);
    }

    string Name() { return "Board"; }
    void KeyDown(unsigned key)
    {
        switch (key)
        {
        case VK_UP:
            _viewer.RotateUp();
            break;
        case VK_DOWN:
            _viewer.RotateDown();
            break;
        case VK_LEFT:
            _viewer.RotateLeft();
            break;
        case VK_RIGHT:
            _viewer.RotateRight();
            break;
        case 0x57:
            _viewer.GoForward();
            break;
        case 0x53:
            _viewer.GoBack();
            break;
        case 0x41:
            _viewer.GoLeft();
            break;
        case 0x44:
            _viewer.GoRight();
            break;
        default:
            break;
        }
        _program.SetUniformMatrix4fv("TRANSFORM_LOCAL2NDC", _viewer.GetMatWorld2NDC());
    }

private:
    void InitProgram()
    {
        const string vertex_shader_str = R"(
            #version 330 core
            layout (location = 0) in vec3 pos;
            uniform mat4 TRANSFORM_LOCAL2NDC;
            
            void main(void) {
                gl_Position = TRANSFORM_LOCAL2NDC * vec4(pos, 1.0);
            }
        )";

        const string fragment_shader_str = R"(
            #version 330 core
            out vec4 color;
            uniform vec4 COLOR;
            void main(void) {
                color = COLOR;
            }
        )";

        map<GLenum, string> shaders;
        shaders[GL_VERTEX_SHADER] = vertex_shader_str;
        shaders[GL_FRAGMENT_SHADER] = fragment_shader_str;
        _program.LoadShaders(shaders);
    }

    void InitBuffers()
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        vector<float> data;
        data.reserve(2 * 3 * 201 * 2);

        for (int i = 0; i <= 100; i++) {
            data.push_back(-100.0f);
            data.push_back(float(i));
            data.push_back(0.0f);
            data.push_back(100.0f);
            data.push_back(float(i));
            data.push_back(0.0f);

            data.push_back(float(i));
            data.push_back(-100.0f);
            data.push_back(0.0f);
            data.push_back(float(i));
            data.push_back(100.0f);
            data.push_back(0.0f);
            if (i > 0) {
                data.push_back(-100.0f);
                data.push_back(-float(i));
                data.push_back(0.0f);
                data.push_back(100.0f);
                data.push_back(-float(i));
                data.push_back(0.0f);

                data.push_back(-float(i));
                data.push_back(-100.0f);
                data.push_back(0.0f);
                data.push_back(-float(i));
                data.push_back(100.0f);
                data.push_back(0.0f);
            }
        }
        glGenBuffers(1, &_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, _buffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * data.size(), &data[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);
    }

private:
    Program _program;
    GLuint _buffer;
    GLuint _vao;
    Viewer _viewer;
};