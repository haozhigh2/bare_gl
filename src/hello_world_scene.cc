#include "scene.h"

static string vertex_shader_str = R"(#version 330 core
    layout (location = 0) in vec3 pos;
    
    void main(void) {
        gl_Position = vec4(pos, 1.0);
    }
)";

static string fragment_shader_str = R"(#version 330 core
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

GLuint tbuffer;
void HelloWorldScene::InitBuffers() {
    static GLfloat data[9] {
        -0.7f, 1.0f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.3f, -0.5f, 0.5f
    };
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 3 * 4, data, GL_STATIC_DRAW);

	glGenBuffers(1, &tbuffer);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tbuffer);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, 1024, NULL, GL_DYNAMIC_COPY);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbuffer);
}


void HelloWorldScene::Draw() {
    _program.Use();
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBeginTransformFeedback(GL_TRIANGLES);

    GLint int_value;
    glGetIntegerv(GL_CURRENT_PROGRAM, &int_value);

    glDrawArrays(GL_TRIANGLES, 0, 3);

	glEndTransformFeedback();
    void* data = glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);
    float* data_float = (float*)data;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}