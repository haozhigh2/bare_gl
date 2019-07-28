#include "mat.h"
#include <math.h>


class Viewer {
public:
    Viewer() {};
    Viewer(float alpha, float r) {
        SetFrustum(alpha, r);
    };
    ~Viewer() {};

    void LookAt(vec3 forward) {
        forward.Normalize();
        _theta = acos(forward[2]);
        _phi = acos(forward[0] / sin(_theta));
        if (forward[1] < 0)
            _phi = 2 * PI - _phi;
        CalculateMatWorld2View();
    }

    void SetLoc(vec3 loc) {
        _loc = loc;
        CalculateMatWorld2View();
    }

    void RotateUp() {
        if (_theta - _step_angle > 0)
            _theta -= _step_angle;
        CalculateMatWorld2View();
    }

    void RotateDown() {
        if (_theta + _step_angle < PI)
            _theta += _step_angle;
        CalculateMatWorld2View();
    }

    void RotateLeft() {
        _phi += _step_angle;
        if (_phi > PI * 2.0f)
            _phi -= PI * 2.0f;
        CalculateMatWorld2View();
    }
    void RotateRight() {
        _phi -= _step_angle;
        if (_phi < 0.0f)
            _phi += PI * 2.0f;
        CalculateMatWorld2View();
    }


    void SetFrustum(float alpha, float r) {
        _r = r;
        _alpha = alpha;
        CalculateMatProject();
    }

    const mat4& GetMatWorld2View() const {
        return _mat_world2view;
    }

    const mat4& GetMatProject() const {
        return _mat_project;
    }

    const mat4& GetMatWorld2NDC() const {
        return _mat_world2ndc;
    }

private:
    void CalculateMatWorld2View() {
        vec3 z{ -sin(_theta) * cos(_phi), -sin(_theta) * sin(_phi), -cos(_theta) };
        vec3 x{ vec3{0.0f, 0.0f, 1.0f}.Cross(z) };
        vec3 y{ z.Cross(x) };

        x.Normalize();
        y.Normalize();
        z.Normalize();

        mat3 P{ x, y, z };
        mat3 P_inv{ P.Transpose() };

        vec3 eye_transformed{ P_inv * _loc };
        _mat_world2view = mat4{ P_inv[0][0], P_inv[0][1], P_inv[0][2], -eye_transformed[0],
                                P_inv[1][0], P_inv[1][1], P_inv[1][2], -eye_transformed[1],
                                P_inv[2][0], P_inv[2][1], P_inv[2][2], -eye_transformed[2],
                                0,                0,                0,                1 };
        _mat_world2ndc = _mat_project * _mat_world2view;
    }

    void CalculateMatProject() {
        _mat_project = mat4{
            1 / (_r * tan(_alpha / 2)), 0, 0, 0,
            0,        1 / tan(_alpha / 2), 0, 0,
            0,                          0, 0, 1,
            0,                          0, -1, 0
        };
        _mat_world2ndc = _mat_project * _mat_world2view;
    }

private:
    // viewer location and direction
    vec3 _loc{ 0 };
    float _theta{ 0 };
    float _phi{ 0 };

    // viewer frustum charactistics
    float _r{ 0 };       // ratio of frustum width to height
    float _alpha{ 0 };   // vertical view angle of frustum

    mat4 _mat_world2view{ 0 };
    mat4 _mat_project{ 0 };
    mat4 _mat_world2ndc{ 0 };

    const float _step_angle{ PI / 32 };
};