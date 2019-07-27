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

    _viewer.SetLoc(vec3{ 0.0f, 0.0f, 1.7f });
    _viewer.SetFrustum(PI / 2.0f, 1.6f);
    _viewer.LookAt(vec3{ 0.0f, 1.0f, -0.8f });

    _uniforms.push_back(make_unique<Uniform4f>(string("COLOR"), 0.9f, 0.9f, 0.9f, 0.9f));
    _uniforms.push_back(make_unique<UniformMatrix4fv>(string("TRANSFORM_LOCAL2NDC"), _viewer.GetMatWorld2NDC().Data()));

	InitBuffers();
}

SceneBoard::~SceneBoard() {
	if (_buffer != 0)
		glDeleteBuffers(1, &_buffer);
}

void SceneBoard::InitBuffers() {
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
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void SceneBoard::Draw() {
    _program.Use();
    for (const auto& uniform : _uniforms)
        uniform->Set();

    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINES, 0, 201 * 2 * 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}