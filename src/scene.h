#pragma once

#include <string>
using namespace std;

#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include "gl_load_proc.h"
#include "program.h"

class Scene {
public:
	Scene() {};
	~Scene() {};

	virtual void Draw() = 0;

protected:
};

class SceneHelloWorld : public Scene {
public:
	SceneHelloWorld();
	~SceneHelloWorld();

	void Draw();

private:
	void InitBuffers();

private:
	Program _program;
	GLuint _buffer;
};