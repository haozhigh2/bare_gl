#pragma once

#include <string>
#include <map>
#include <vector>
using namespace std;

#include <GL/GL.h>
#include <gl/GLU.h>
#include "gl_load_proc.h"

class Texture2D
{
    

private:
    GLuint _id;
    GLsizei _width;
    GLsizei _height;
    GLenum _format;
    GLenum _type;
};