#include "tool/mat.h"
#include <math.h>

class ViewerBase
{
public:
    ViewerBase(){}

    ViewerBase(float alpha, float r) { SetFrustum(alpha, r); };

    ~ViewerBase(){};

    void LookAt(vec3 forward)
    {
        forward = forward.Normalize();
        _theta = acos(forward[2]);
        _phi = acos(forward[0] / sin(_theta));
        if (forward[1] < 0)
            _phi = 2 * PI - _phi;
    }

    void SetLoc(vec3 loc)
    {
        _loc = loc;
    }

    void RotateUp()
    {
        if (_theta - _step_angle > 0)
            _theta -= _step_angle;
    }

    void RotateDown()
    {
        if (_theta + _step_angle < PI)
            _theta += _step_angle;
    }

    void RotateLeft()
    {
        _phi += _step_angle;
        if (_phi > PI * 2.0f)
            _phi -= PI * 2.0f;
    }

    void RotateRight()
    {
        _phi -= _step_angle;
        if (_phi < 0.0f)
            _phi += PI * 2.0f;
    }

    void GoForward()
    {
        vec3 forward_xy{sin(_theta) * cos(_phi), sin(_theta) * sin(_phi), 0.0f};
        forward_xy = forward_xy.Normalize();
        _loc += forward_xy * _step_loc;
    }

    void GoBack()
    {
        vec3 forward_xy{sin(_theta) * cos(_phi), sin(_theta) * sin(_phi), 0.0f};
        forward_xy = forward_xy.Normalize();
        _loc -= forward_xy * _step_loc;
    }

    void GoLeft()
    {
        vec3 forward_xy{sin(_theta) * cos(_phi), sin(_theta) * sin(_phi), 0.0f};
        forward_xy = forward_xy.Normalize();
        _loc += vec3{-forward_xy[1], forward_xy[0], 0.0f} * _step_loc;
    }

    void GoRight()
    {
        vec3 forward_xy{sin(_theta) * cos(_phi), sin(_theta) * sin(_phi), 0.0f};
        forward_xy = forward_xy.Normalize();
        _loc += vec3{forward_xy[1], -forward_xy[0], 0.0f} * _step_loc;
    }

    void SetFrustum(float alpha, float r)
    {
        _r = r;
        _alpha = alpha;
    }

protected:
    vec3 _loc{0};           // viewer location
    float _theta{0};        // viewing direction
    float _phi{0};          // viewing direction

    float _r{0};            // ratio of frustum width to height
    float _alpha{0};        // vertical view angle of frustum

    const float _step_angle{PI / 32};
    const float _step_loc{0.1f};
};

class Viewer : public ViewerBase
{
public:
    Viewer(){};
    Viewer(float alpha, float r) : ViewerBase(alpha, r) {}

    void GetTransforms(mat4& world2view, mat4& world2ndc)
    {

        vec3 z{-sin(_theta) * cos(_phi), -sin(_theta) * sin(_phi), -cos(_theta)};
        vec3 x{vec3{0.0f, 0.0f, 1.0f}.Cross(z)};
        vec3 y{z.Cross(x)};

        x = x.Normalize();
        y = y.Normalize();
        z = z.Normalize();

        mat3 P{x, y, z};
        mat3 P_inv{P.Transpose()};

        vec3 eye_transformed{P_inv * _loc};
        world2view = mat4{P_inv[0][0], P_inv[0][1], P_inv[0][2], -eye_transformed[0],
                               P_inv[1][0], P_inv[1][1], P_inv[1][2], -eye_transformed[1],
                               P_inv[2][0], P_inv[2][1], P_inv[2][2], -eye_transformed[2],
                               0, 0, 0, 1};

        mat4 project {
            1 / (_r * tan(_alpha / 2)), 0, 0, 0,
            0, 1 / tan(_alpha / 2), 0, 0,
            0, 0, 0, 1,
            0, 0, -1, 0};

        world2ndc = project * world2view;
    }

protected:
    //mat4 _mat_world2view{0};    // world to view space transform matrix
    //mat4 _mat_project{0};       // projection transform matrix
    //mat4 _mat_world2ndc{0};     // world to ndc space transform matrix
};