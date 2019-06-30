#include "scene.h"

static string vertex_shader_str = R"(
    layout (location = 0) in vec3 pos;
    
    void main() {
        gl_Position = vec4(pos, 1.0);
    }
)";

static string fragment_shader_str = R"(
    void main() {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

HelloWorldScene::HelloWorldScene() {
    map<GLuint, string> shaders;
    shaders[GL_VERTEX_SHADER] = vertex_shader_str;
    shaders[GL_FRAGMENT_SHADER] = fragment_shader_str;
    _program.LoadShaders(shaders);
}

void HelloWorldScene::Draw() {
    _program.Use();

}