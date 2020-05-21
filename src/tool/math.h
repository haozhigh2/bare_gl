
#include "mat.h"

#include <random>
using namespace std;

class RandomReal
{
public:
    RandomReal(float min, float max): _min(min), _max(max), _uniform_real(_min, _max)
    {
        random_device device;
        _mt19937.seed(device());
    }

    float Next()
    {
        return _uniform_real(_mt19937);
    }

private:
    float _min;
    float _max;
    mt19937 _mt19937;
    uniform_real_distribution<float> _uniform_real;
};

class RandomUnitVector
{
public:
    RandomUnitVector() : _rand(-1.0f, 1.0f){}

    vec3 Next()
    {
        vec3 v;
        do
        {
            v[0] = _rand.Next();
            v[1] = _rand.Next();
            v[2] = _rand.Next();
        } while (v.Len() > 1.0f);
        return v.Normalize();
    }

private:
    RandomReal _rand;
};