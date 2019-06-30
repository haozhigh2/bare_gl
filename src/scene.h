#pragma once

#include <string>
using namespace std;

#include "common.h"
#include "program.hpp"

class Scene {
public:
	Scene() {};
	~Scene() {};

	virtual void Draw() = 0;

protected:
};

class HelloWorldScene : public Scene {
public:
	HelloWorldScene();
	~HelloWorldScene(){};

	void Draw();

private:
	Program _program;
};