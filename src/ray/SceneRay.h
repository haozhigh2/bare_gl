#pragma once

#include "tool/mat.h"
#include "scene/scene.h"

#include <limits>
#ifdef max
    #undef max
#endif
#ifdef min 
    #undef min
#endif

class Ray
{
public:
    Ray(const vec3 &origin, const vec3 &direction) : _origin(origin), _direction(direction.Normalize()) {}

    const vec3 &Origin() const { return _origin; }
    const vec3 &Direction() const { return _direction; }

    vec3 At(float t) const { return _origin + _direction * t; }

private:
    vec3 _origin;
    vec3 _direction;
};

struct HitRecord
{
    float t;
    vec3 point;
    vec3 normal;
};

class Hittable
{
public:
    virtual bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &record) const = 0;
};

class HittableList
{
public:
    virtual void Add(unique_ptr<Hittable> hittable)
    {
        _list.push_back(std::move(hittable));
    }

    virtual bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &record) const
    {
        HitRecord tmp_record;
        bool hit_anything{false};
        float min_t{t_max};
        for (const auto& p_hittable : _list)
        {
            if (p_hittable->Hit(ray, t_min, min_t, tmp_record))
            {
                hit_anything = true;
                min_t = tmp_record.t;
                record = tmp_record;
            }
        }
        return hit_anything;
    }

private:
    vector<unique_ptr<Hittable>> _list;
};

class Sphere : public Hittable
{
public:
    Sphere(const vec3 &origin, const float radius) : _origin(origin), _radius(radius) {}

    const vec3 &Origin() const { return _origin; }
    float Radius() const { return _radius; }

    bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &record) const
    {
        vec3 v0{_origin - ray.Origin()};
        if (v0.Len2() <= _radius * _radius)
            return false;

        float x{v0.Dot(ray.Direction())};
        if (x <= 0)
            return false;

        vec3 v1{ray.Direction() * x};
        if (v0.Len2() - v1.Len2() > _radius * _radius)
            return false;

        float t{x - sqrt(_radius * _radius - (v0.Len2() - v1.Len2()))};
        if (t < t_min || t > t_max)
            return false;

        record.t = t;
        record.point = ray.At(t);
        record.normal = (record.point - _origin).Normalize();
        return true;
    }

private:
    vec3 _origin;
    float _radius;
};

class ViewerRay : public ViewerBase
{
public:
    ViewerRay(){}
    ViewerRay(float alpha, float r) : ViewerBase(alpha, r) {}

    Ray RayAtScreen(int screen_pixel_width, int screen_pixel_height, int screen_pixel_x, int screen_pixel_y)
    {
        /*
        ** axis vector of view space in world space
        */
        vec3 z{-sin(_theta) * cos(_phi), -sin(_theta) * sin(_phi), -cos(_theta)};
        vec3 x{vec3{0.0f, 0.0f, 1.0f}.Cross(z)};
        vec3 y{z.Cross(x)};

        x = x.Normalize();
        y = y.Normalize();
        z = z.Normalize();

        float screen_half_height{1.0f};
        float screen_half_width{_r};

        vec3 direction{-z * (screen_half_height / tan(_alpha / 2.0f))};
        direction += x * ((screen_pixel_x * 2 + 1 - screen_pixel_width) * screen_half_width / screen_pixel_width);
        direction -= y * ((screen_pixel_y * 2 + 1 - screen_pixel_height) * screen_half_height / screen_pixel_height);
        direction = direction.Normalize();

        return Ray(_loc, direction);
    }
};

class SceneRay : public SceneBase
{
public:
    SceneRay() : _buffer(0), _vao(0), _texture(0), _width(0), _height(0)
    {
        _viewer.SetLoc(vec3{0.0f, 0.0f, 1.7f});
        _viewer.LookAt(vec3{0.0f, 1.0f, 0.0f});

        InitProgram();
        InitBuffers();

        _program.SetUniform1i("color_texture", 0);

        _hittable_list.Add(make_unique<Sphere>(vec3({0.0f, 1.0f, 1.7f}), 0.5f));
        _hittable_list.Add(make_unique<Sphere>(vec3({0.0f, 1.0f, 1.7f - 105.0f}), 100.0f));
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
                HitRecord record;
                if (_hittable_list.Hit(ray, 0.0f, numeric_limits<float>::max(), record))
                {
                    SetColor(x, y, vec3({record.normal[0] + 1.0f, record.normal[2] + 1.0f, -record.normal[1] + 1.0f}) * 0.5f);
                }
                else
                {
                    float t{0.5f * (ray.Direction()[2] + 1.0f)};
                    vec3 color{vec3({1.0f, 1.0f, 1.0f}) * (1.0f - t) + vec3({0.5f, 0.7f, 1.0f}) * t};
                    SetColor(x, y, color);
                }
            }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, _width, _height, 0, GL_RGB, GL_FLOAT, _data.data());
    }

    string Name() { return "Ray"; }

    void KeyDown(unsigned key)
    {
        switch (key)
        {
        case VK_UP:
            _viewer.RotateUp();
            break;
        case VK_DOWN:
            _viewer.RotateDown();
            break;
        case VK_LEFT:
            _viewer.RotateLeft();
            break;
        case VK_RIGHT:
            _viewer.RotateRight();
            break;
        case 0x57:
            _viewer.GoForward();
            break;
        case 0x53:
            _viewer.GoBack();
            break;
        case 0x41:
            _viewer.GoLeft();
            break;
        case 0x44:
            _viewer.GoRight();
            break;
        default:
            break;
        }
        Update();
    }

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

    ViewerRay _viewer;

    HittableList _hittable_list;
};