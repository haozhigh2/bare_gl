#pragma once

#include <string>

using namespace std;

#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include "gl_load_proc.h"
#include "program.h"
#include "uniform.h"
#include "viewer.h"

class Scene {
public:
	Scene() {};
	~Scene() {};

	virtual void Draw() = 0;
    virtual string Name() = 0;
    virtual void KeyDown(unsigned key) = 0;

    void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height) { glViewport(x, y, width, height); }

protected:
};

class SceneHelloWorld : public Scene {
public:
	SceneHelloWorld();
	~SceneHelloWorld();

	void Draw();
    string Name();
    void KeyDown(unsigned key) {};

private:
	void InitBuffers();

private:
	Program _program;
	GLuint _buffer;
};

class SceneBoard : public Scene {
public:
	SceneBoard();
	~SceneBoard();

	void Draw();
    string Name();
    void KeyDown(unsigned key);

private:
	void InitBuffers();

private:
	Program _program;
    vector<unique_ptr<UniformBase>> _uniforms;
	GLuint _buffer;
    Viewer _viewer;
};