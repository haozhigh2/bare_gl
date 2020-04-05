#pragma once

#include "tool/mat.h"
#include "scene/scene.h"

class Ray
{
public:
    Ray(const vec3 &origin, const vec3 &direction) : _origin(origin), _direction(direction)
    {
        _direction.Normalize();
    }

    const vec3 &Origin() const { return _origin; }
    const vec3 &Direction() const { return _direction; }

private:
    vec3 _origin;
    vec3 _direction;
};

class Sphere
{
public:
    Sphere(const vec3 &origin, const float radius) : _origin(origin), _radius(radius) {}

    const vec3 &Origin() const { return _origin; }
    float Radius() const { return _radius; }

private:
    vec3 _origin;
    float _radius;
};

bool inside(const vec3& point, const Sphere& sphere)
{
    vec3 v{sphere.Origin() - point};
    return v.Len2() <= sphere.Radius() * sphere.Radius();
}

bool intersect(const Ray& ray, const Sphere& sphere)
{
    if(inside(ray.Origin(), sphere))
        return false;

    vec3 v0{sphere.Origin() - ray.Origin()};
    float x{v0.Dot(ray.Direction())};
    if (x <= 0)
        return false;

    vec3 v1{ray.Direction() * x};
    return (v0.Len2() - v1.Len2() <= sphere.Radius() * sphere.Radius());
}

class SceneRay : public SceneBase
{
public:
    SceneRay(): _buffer(0), _vao(0), _texture(0), _width(0), _height(0)
    {
        _viewer.SetLoc(vec3{0.0f, 0.0f, 1.7f});
        _viewer.LookAt(vec3{0.0f, 1.0f, 0.0f});

        InitProgram();
        InitBuffers();

        _program.SetUniform1i("color_texture", 0);
    }

    ~SceneRay()
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
        if (glIsTexture(_texture))
        {
            glDeleteTextures(1, &_texture);
            _texture = 0;
        }
    }

    void Draw()
    {
        if (!glIsTexture(_texture))
            return;

        glClear(GL_COLOR_BUFFER_BIT);

        _program.Use();
        glBindVertexArray(_vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Update()
    {
        for (int x = 0; x < _width; x++)
            for (int y = 0; y < _height; y++)
            {
                Ray ray{_viewer.RayAtScreen(_width, _height, x, y)};
                float t{0.5f * (ray.Direction()[2] + 1.0f)};
                vec3 color{vec3({1.0f, 1.0f, 1.0f}) * (1.0f - t) + vec3({0.5f, 0.7f, 1.0f}) * t};
                SetColor(x, y, color);
            }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, _width, _height, 0, GL_RGB, GL_FLOAT, _data.data());
    }

    string Name() { return "Ray"; }

    void KeyDown(unsigned key) {}

    void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        SceneBase::SetViewport(x, y, width, height);
        _viewer.SetFrustum(PI / 2.0f, (float)width / height);
        this->InitTextures(width, height);
        Update();
    }

private:
    void InitProgram()
    {
        const string vertex_shader_str = R"(
            #version 330 core

            layout (location = 0) in vec3 pos;
            layout (location = 1) in vec2 uv;

            out vec2 frag_uv;
            
            void main(void)
            {
                gl_Position = vec4(pos, 1.0);
                frag_uv = uv;
            }
        )";

        const string fragment_shader_str = R"(
            #version 330 core

            in vec2 frag_uv;

            uniform sampler2D color_texture;

            out vec3 color;

            void main(void)
            {
                color = texture(color_texture, frag_uv).rgb;
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

        vector<float> data
        {
            -1.0,  1.0, 0.0, 0.0, 0.0,
            -1.0, -1.0, 0.0, 0.0, 1.0,
             1.0,  1.0, 0.0, 1.0, 0.0,
            -1.0, -1.0, 0.0, 0.0, 1.0,
             1.0, -1.0, 0.0, 1.0, 1.0,
             1.0,  1.0, 0.0, 1.0, 0.0
        };

        glGenBuffers(1, &_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, _buffer);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, NULL);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
    }

    void InitTextures(int width, int height)
    {
        if (glIsTexture(_texture))
        {
            glDeleteTextures(1, &_texture);
            _texture = 0;
        }
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        _width = width;
        _height = height;
        _data.resize(width * height * 3);
        //for (int w = 0; w < width; w++)
        //    for (int h = 0; h < height; h++)
        //    {
        //        if (h / 10 % 7 == 0)
        //            SetColor(w, h, {1.0f, 0.0f, 0.0f});
        //        else
        //            SetColor(w, h, {0.0f, 0.0f, 0.0f});
        //    }
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, _data.data());
    }

    void SetColor(int x, int y, vec3 color)
    {
        assert(x >= 0 && x < _width && y >= 0 && y < _height);
        _data[(y * _width + x) * 3] = color[0];
        _data[(y * _width + x) * 3 + 1] = color[1];
        _data[(y * _width + x) * 3 + 2] = color[2];
    }

private:
    Program _program;
    GLuint _buffer;
    GLuint _texture;
    GLuint _vao;

    int _width;
    int _height;
    vector<float> _data;

    Viewer _viewer;
};