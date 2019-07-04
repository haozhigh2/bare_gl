#include "scene.h"

static string vertex_shader_str = R"(
	#version 330 core
    layout (location = 0) in vec3 pos;
    
    void main(void) {
        gl_Position = vec4(pos, 1.0);
    }
)";

static string fragment_shader_str = R"(
	#version 330 core
	out vec4 color;
    void main(void) {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

HelloWorldScene::HelloWorldScene(): _buffer(0) {
    map<GLenum, string> shaders;
    shaders[GL_VERTEX_SHADER] = vertex_shader_str;
    shaders[GL_FRAGMENT_SHADER] = fragment_shader_str;
    _program.LoadShaders(shaders);

	InitBuffers();
}

HelloWorldScene::~HelloWorldScene() {
	if (_buffer != 0)
		glDeleteBuffers(1, &_buffer);
}

void HelloWorldScene::InitBuffers() {
    GLfloat data[9] {
        0.0, 1.0, 0.5,
        -1.0, 0.0, 0.5,
        0.0, -1.0, 0.5
    };
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 3 * 4, data, GL_STATIC_DRAW);
}

void HelloWorldScene::Draw() {
    _program.Use();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}