#include "mat.h"
#include "scene.h"

static string vertex_shader_str = R"(
    #version 330 core
    layout (location = 0) in vec3 pos;
    uniform mat4 TRANSFORM_LOCAL2NDC;
    
    void main(void) {
        gl_Position = MAT_LOCAL_TO_NDC * vec4(pos, 1.0);
    }
)";

static string fragment_shader_str = R"(
    #version 330 core
	out vec4 color;
    uinform float4 COLOR;
    void main(void) {
        color = COLOR;
    }
)";

SceneBoard::SceneBoard(): _buffer(0) {
    map<GLenum, string> shaders;
    shaders[GL_VERTEX_SHADER] = vertex_shader_str;
    shaders[GL_FRAGMENT_SHADER] = fragment_shader_str;
    _program.LoadShaders(shaders);

    _uniforms.push_back(make_unique<Uniform4f>(0.9f, 0.9f, 0.9f, 0.9f));

    _viewer.SetLoc(vec3{ 0.0f, 0.0f, 1.7f });
    _viewer.SetFrustum(PI / 2.0f, 1.6f);

    mat4 world_mat(mat4::UnitMat());
    mat4 view_mat;
    mat4 project_mat;

	InitBuffers();
}

SceneBoard::~SceneBoard() {
	if (_buffer != 0)
		glDeleteBuffers(1, &_buffer);
}

void SceneBoard::InitBuffers() {
    static GLfloat data[] {
        -100.0f, 0.0f, 0.0f,
         100.0f, 0.0f, 0.0f,
         0.0f,  100.0f, 0.0f,
         0.0f, -100.0f, 0.0f
    };
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * 4 * 4, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void SceneBoard::Draw() {
    _program.Use();
    for (const auto& uniform : _uniforms)
        uniform->Set();
    glBindBuffer(GL_LINES, _buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}