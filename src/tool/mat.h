#pragma once

#include <cmath>
#include <iostream>
#include <initializer_list>
using namespace std;

#define PI 3.141592653f

template <typename T, unsigned N>
struct Vec
{
    typedef Vec<T, N> TypeName;

    Vec<T, N>()
    {
        for (int i = 0; i < N; i++)
            _data[i] = 0;
    }

    Vec<T, N>(initializer_list<T> values)
    {
        if (values.size() == 1)
            *this = *(values.begin());
        else
        {
            auto it{values.begin()};
            for (int i = 0; i < N; i++)
                _data[i] = *it++;
        }
    }

    Vec<T, N>(const TypeName &v)
    {
        for (int i = 0; i < N; i++)
            _data[i] = v._data[i];
    }

    T& operator[](unsigned i)
    {
        return _data[i];
    }

    const T& operator[](unsigned i) const
    {
        return _data[i];
    }

    T *Data()
    {
        return &_data[0];
    }

    const T *Data() const
    {
        return &_data[0];
    }

    void operator=(T x)
    {
        for (auto &it : _data)
            it = x;
    }

    void operator=(const TypeName &rhs)
    {
        for (int i = 0; i < N; i++)
            _data[i] = rhs._data[i];
    }

    void operator+=(T x)
    {
        for (auto &it : _data)
            it += x;
    }

    void operator+=(const TypeName &rhs)
    {
        for (int i = 0; i < N; i++)
            _data[i] += rhs._data[i];
    }

    void operator-=(T x)
    {
        for (auto &it : _data)
            it -= x;
    }

    void operator-=(const TypeName &rhs)
    {
        for (int i = 0; i < N; i++)
            _data[i] -= rhs._data[i];
    }

    void operator*=(T x)
    {
        for (auto &it : _data)
            it *= x;
    }

    void operator/=(T x)
    {
        for (auto &it : _data)
            it /= x;
    }

    TypeName operator+(T x) const
    {
        TypeName result{*this};
        result += x;
        return result;
    }

    TypeName operator+(const TypeName &rhs) const
    {
        TypeName result{*this};
        result += rhs;
        return result;
    }

    TypeName operator-(T x) const
    {
        TypeName result{*this};
        result -= x;
        return result;
    }

    TypeName operator-(const TypeName &rhs) const
    {
        TypeName result{*this};
        result -= rhs;
        return result;
    }

    TypeName operator*(T x) const
    {
        TypeName result{*this};
        result *= x;
        return result;
    }

    TypeName operator/(T x) const
    {
        TypeName result{*this};
        result /= x;
        return result;
    }

    T Dot(const TypeName &rhs) const
    {
        T result{0};
        for (int i = 0; i < N; i++)
            result += _data[i] * rhs._data[i];
        return result;
    }

    TypeName Cross(const TypeName &rhs) const
    {
        assert(N == 3);
        return Vec<T, 3>{_data[1] * rhs._data[2] - _data[2] * rhs._data[1],
                         _data[2] * rhs._data[0] - _data[0] * rhs._data[2],
                         _data[0] * rhs._data[1] - _data[1] * rhs._data[0]};
    }

    T Len() const
    {
        T sum{0};
        for (const auto &it : _data)
            sum += it * it;
        return static_cast<T>(sqrt(static_cast<double>(sum)));
    }

    void Normalize()
    {
        this->operator/=(Len());
    }

private:
    T _data[N];
};

typedef Vec<float, 2> vec2;
typedef Vec<int, 2> ivec2;
typedef Vec<unsigned, 2> uivec2;

typedef Vec<float, 3> vec3;
typedef Vec<int, 3> ivec3;
typedef Vec<unsigned, 3> uivec3;

typedef Vec<float, 4> vec4;
typedef Vec<int, 4> ivec4;
typedef Vec<unsigned, 4> uivec4;

template <typename T, unsigned ROW, unsigned COL>
struct Mat
{
    typedef Mat<T, ROW, COL> TypeName;

    Mat<T, ROW, COL>(initializer_list<T> values)
    {
        if (values.size() == 1)
            *this = *(values.begin());
        else
        {
            assert(values.size() == ROW * COL);
            auto it{values.begin()};
            for (unsigned i = 0; i < ROW * COL; i++)
                _data[i] = *it++;
        }
    }

    Mat<T, ROW, COL>(initializer_list<Vec<T, ROW>> rows)
    {
        assert(rows.size() == COL);
        auto it{rows.begin()};
        for (unsigned c = 0; c < COL; c++)
        {
            for (unsigned r = 0; r < ROW; r++)
                (*this)[r][c] = (*it)[r];
            it++;
        }
    }
    
    Mat<T, ROW, COL>(const TypeName &rhs)
    {
        *this = rhs;
    }

    T* operator[](unsigned r)
    {
        assert(r >= 0 && r < ROW);
        return &_data[r * COL];
    }

    const T* operator[](unsigned r) const
    {
        assert(r >= 0 && r < ROW);
        return &_data[r * COL];
    }

    T *Data()
    {
        return &_data[0];
    }

    const T *Data() const
    {
        return &_data[0];
    }

    void operator=(const TypeName &rhs)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] = rhs._data[i];
    }

    void operator=(const T x)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] = x;
    }

    TypeName operator+(const TypeName &rhs) const
    {
        TypeName result{*this};
        result += rhs;
        return result;
    }

    TypeName operator+(T x) const
    {
        TypeName result{*this};
        result += x;
        return x;
    }

    void operator+=(const TypeName &rhs)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] += rhs._data[i];
    }

    void operator+=(T x)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] += x;
    }

    TypeName operator-(const TypeName &rhs) const
    {
        TypeName result{*this};
        result -= rhs;
        return result;
    }

    TypeName operator-(T x) const
    {
        TypeName result{*this};
        result -= x;
        return x;
    }

    void operator-=(const TypeName &rhs)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] -= rhs._data[i];
    }

    void operator-=(T x)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] -= x;
    }

    template<unsigned COL2>
    Mat<T, ROW, COL2> operator*(const Mat<T, COL, COL2> &rhs) const
    {
        Mat<T, ROW, COL2> result{0};
        for (int r = 0; r < ROW; r++)
            for (int c = 0; c < COL2; c++)
                for (int i = 0; i < COL; i++)
                    result[r][c] += (*this)[r][i] * rhs[i][c];
        return result;
    }

    TypeName operator*(T x) const
    {
        TypeName result{*this};
        result *= x;
        return result;
    }

    Vec<T, ROW> operator*(const Vec<T, COL> &v) const
    {
        Vec<T, ROW> result{0};
        for (int r = 0; r < ROW; r++)
            for (int c = 0; c < COL; c++)
                result[r] += (*this)[r][c] * v[c];
        return result;
    }

    void operator*=(T x)
    {
        for (unsigned i = 0; i < ROW * COL; i++)
            _data[i] *= x;
    }

    void Replace(int r0, int r1, T x)
    {
        for (int c = 0; c < COL; c++)
            (*this)[r0][c] += (*this)[r1][c] * x;
    }

    void Interchange(int r0, int r1)
    {
        for (int c = 0; c < COL; c++)
        {
            T tmp = (*this)[r0][c];
            (*this)[r0][c] = (*this)[r1][c];
            (*this)[r1][c] = tmp;
        }
    }

    void Scale(int r, T x)
    {
        for (unsigned c = 0; c < COL; c++)
            (*this)[r][c] *= x;
    }

    T Det() const
    {
        assert(ROW == COL);
        const unsigned N = ROW;
        T det{1};
        TypeName m{*this};
        for (int r = 0; r < N - 1; r++)
        {
            int r_max{r};
            for (int r_tmp = r + 1; r_tmp < N; r_tmp++)
                if (m[r_tmp][r] > m[r_max][r])
                    r_max = r_tmp;

            if (r_max != r)
            {
                det *= -1;
                m.Interchange(r, r_max);
            }

            for (int r1 = r + 1; r1 < N; r1++)
                m.Replace(r1, r, -m[r1][r] / m[r][r]);
        }
        for (int r = 0; r < N; r++)
            det *= m[r][r];
        return det;
    }

    TypeName Inv() const
    {
        assert(ROW == COL);
        const unsigned N = ROW;
        TypeName m{*this};
        TypeName result{TypeName::UnitMat()};
        for (int r = 0; r < N - 1; r++)
        {
            int r_max{r};
            for (int r_tmp = r + 1; r_tmp < N; r_tmp++)
                if (abs(m[r_tmp][r]) > abs(m[r_max][r]))
                    r_max = r_tmp;

            if (r_max != r)
            {
                m.Interchange(r, r_max);
                result.Interchange(r, r_max);
            }

            for (int r1 = r + 1; r1 < N; r1++)
            {
                T tmp{-m[r1][r] / m[r][r]};
                m.Replace(r1, r, tmp);
                result.Replace(r1, r, tmp);
            }
        }
        for (int r = N - 1; r > 0; r--)
            for (int r1 = r - 1; r1 >= 0; r1--)
            {
                T tmp{-m[r1][r] / m[r][r]};
                result.Replace(r1, r, tmp);
            }
        for (int r = 0; r < N; r++)
        {
            result.Scale(r, 1 / m[r][r]);
        }
        return result;
    }

    Mat<T, COL, ROW> Transpose() const
    {
        Mat<T, COL, ROW> m{0};
        for (int r = 0; r < COL; r++)
            for (int c = 0; c < ROW; c++)
                m[r][c] = (*this)[c][r];
        return m;
    }

    static TypeName UnitMat()
    {
        assert(ROW == COL);
        TypeName result{0};
        for (int r = 0; r < ROW; r++)
            result[r][r] = 1;
        return result;
    }

private:
    T _data[ROW * COL];
};

typedef Mat<float, 2, 2> mat2;
typedef Mat<int, 2, 2> imat2;
typedef Mat<unsigned, 2, 2> uimat2;

typedef Mat<float, 3, 3> mat3;
typedef Mat<int, 3, 3> imat3;
typedef Mat<unsigned, 3, 3> uimat3;

typedef Mat<float, 4, 4> mat4;
typedef Mat<int, 4, 4> imat4;
typedef Mat<unsigned, 4, 4> uimat4;