

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