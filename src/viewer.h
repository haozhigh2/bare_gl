#include "mat.h"
#include "mat.h"


class Viewer {
public:
    Viewer() {};
    Viewer(float alpha, float r) {
        SetFrustum(alpha, r);
    };
    ~Viewer() {};

    void LookAt(vec3 forward, vec3 up) {
        _forward = forward;
        _up = up;
        CalculateMatWorld2View();
    }

    void SetLoc(vec3 loc) {
        _loc = loc;
        CalculateMatWorld2View();
    }

    void SetFrustum(float alpha, float r) {
        _r = r;
        _alpha = alpha;

        _mat_project = mat4{
            1 / (_r * tan(_alpha / 2)), 0, 0, 0,
            0,        1 / tan(_alpha / 2), 0, 0,
            0,                          0, 0, 1,
            0,                          0, 1, 0
        };
    }

    const mat4& GetMatWorld2View() const {
        return _mat_world2view;
    }

    const mat4& GetMatProject() const {
        return _mat_project;
    }

    mat4 GetMatWorld2NDC() const {
        return  _mat_project * _mat_world2view;
    }

private:
    void CalculateMatWorld2View() {
        vec3 z{ vec3({0}) - _forward };
        vec3 x{ _up.Cross(z) };
        vec3 y{ z.Cross(x) };
        x.Normalize();
        y.Normalize();
        z.Normalize();

        mat3 P{ x, y, z };
        mat3 P_inv{ P.Transpose() };

        vec3 eye_transformed{ P_inv * _loc };
        _mat_world2view = mat4{ P_inv.data[0][0], P_inv.data[0][1], P_inv.data[0][2], -eye_transformed[0],
                                P_inv.data[1][0], P_inv.data[1][1], P_inv.data[1][2], -eye_transformed[1],
                                P_inv.data[2][0], P_inv.data[2][1], P_inv.data[2][2], -eye_transformed[2],
                                0,                0,                0,                1 };
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
};