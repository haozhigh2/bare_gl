#pragma once

#include <cmath>
#include <iostream>
#include <initializer_list>
using namespace std;

#define PI 3.141592653

template <typename T, unsigned N>
struct Vec {
	T data[N];

	typedef Vec<T, N> TypeName;

	// constructor
	Vec<T, N>(initializer_list<T> values) {
        if (values.size() == 1)
            *this = *(values.begin());
		else {
			const T* p{ values.begin() };
            for (int i = 0; i < N; i++)
                data[i] = *p++;
		}
    }
	// copy constructor
	Vec<T, N>(const TypeName& v) {
		for (int i = 0; i < N; i++)
			data[i] = v.data[i];
	}

	inline T& operator[](unsigned i) {
		return data[i];
	}

    inline const T& operator[](unsigned i) const {
        return data[i];
    }

	inline void operator=(T x) {
		for (auto& it : data)
			it = x;
	}

	inline void operator=(const TypeName& rhs) {
		for (int i = 0; i < N; i++)
			data[i] = rhs.data[i];
	}

	inline void operator+=(T x) {
		for (auto& it : data)
			it += x;
	}

	inline void operator+=(const TypeName& rhs) {
		for (int i = 0; i < N; i++)
			data[i] += rhs.data[i];
	}

	inline void operator-=(T x) {
		for (auto& it : data)
			it -= x;
	}

	inline void operator-=(const TypeName& rhs) {
		for (int i = 0; i < N; i++)
			data[i] -= rhs.data[i];
	}

	inline void operator*=(T x) {
		for (auto& it : data)
			it *= x;
	}

	inline void operator/=(T x) {
		for (auto& it : data)
			it /= x;
	}

	inline TypeName operator+(T x) const {
        TypeName result{ *this };
		result += x;
		return result;
	}

	inline TypeName operator+(const TypeName& rhs) const {
		TypeName result{ *this };
		result += rhs;
		return result;
	}

	inline TypeName operator-(T x) const {
		TypeName result{ *this };
		result -= x;
		return result;
	}

	inline TypeName operator-(const TypeName& rhs) const {
		TypeName result{ *this };
		result += rhs;
		return result;
	}

	inline TypeName operator*(T x) const {
		TypeName result{ *this };
		result *= x;
		return result;
	}

    inline TypeName operator/(T x) const {
        TypeName result{ *this };
        result /= x;
        return result;
    }

    /*
    ** dot product and cross product
    */
	inline T Dot(const TypeName& rhs) const {
		T result{ 0 };
		for (int i = 0; i < N; i++)
			result += data[i] * rhs.data[i];
		return result;
	}

    inline TypeName Cross(const TypeName& rhs) const {
        if (N != 3) {
            cerr << "Cross product only supports vector of size 3" << endl;
            exit(-1);
        }
        else {
            return Vec<T, 3>{ data[1] * rhs.data[2] - data[2] * rhs.data[1],
                              data[2] * rhs.data[0] - data[0] * rhs.data[2],
                              data[0] * rhs.data[1] - data[1] * rhs.data[0]};
        }
    }

    /*
    ** length of vector in space
    */
    inline T Len() const {
        T sum{ 0 };
        for (const auto& it : data)
            sum += it * it;
        return static_cast<T>(sqrt(static_cast<double>(sum)));
    }

    inline void Normalize() {
        this->operator/=(Len());
    }
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

template <typename T, unsigned N>
struct Mat {
    T data[N][N];

    typedef Mat<T, N> TypeName;

    Mat<T, N>(initializer_list<T> values) {
        if (values.size() == 1)
            (*this) = *(values.begin());
		else {
			const T* p{ values.begin() };
            for (unsigned r = 0; r < N; r++)
				for (unsigned c = 0; c < N; c++)
					data[r][c] = *p++;
		}

    }
    Mat<T, N>(initializer_list<Vec<T, N>> vecs) {
		const auto* p{ vecs.begin() };
		for (unsigned c = 0; c < N; c++) {
			for (unsigned r = 0; r < N; r++)
				data[r][c] = (*p)[r];
			p++;
		}
	}
	Mat<T, N>(const Mat<T, N>& rhs) {
        for (unsigned r = 0; r < N; r++)
            for (unsigned c = 0; c < N; c++)
                data[r][c] = rhs.data[r][c];
    }

	auto& operator[](unsigned n) {
		return data[n];
	}

	const auto& operator[](unsigned n) const{
		return data[n];
	}

    // operator= and copy constructors
    void operator=(const TypeName& rhs) {
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                data[r][c] = rhs.data[r][c];
    }
    void operator=(const T x) {
        for (auto& it_row : data)
            for (auto& it : it_row)
                it = x;
    }

    // operator+ and operator+=
    TypeName operator+(const TypeName& rhs) const {
        TypeName result{ *this };
        result += rhs;
        return result;
    }
    TypeName operator+(T x) const {
        TypeName result{ *this };
        result += x;
        return x;
    }
    void operator+=(const TypeName& rhs) {
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                data[r][c] += rhs.data[r][c];
    }
    void operator+=(T x) {
        for (auto& it_row : data)
            for (auto& it : it_row)
                it += x;
    }

    // operator- and operator-=
    TypeName operator-(const TypeName& rhs) const {
        TypeName result{ *this };
        result -= rhs;
        return result;
    }
    TypeName operator-(T x) const {
        TypeName result{ *this };
        result -= x;
        return x;
    }
    void operator-=(const TypeName& rhs) {
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                data[r][c] -= rhs.data[r][c];
    }
    void operator-=(T x) {
        for (auto& it_row : data)
            for (auto& it : it_row)
                it -= x;
    }

    // operator* and operator*=
    TypeName operator*(const TypeName& rhs) const {
        TypeName result{ 0 };
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                for (int i = 0; i < N; i++)
                    result[r][c] += data[r][i] * rhs[i][c];
        return result;
    }
    TypeName operator*(T x) const {
        TypeName result{ *this };
        result *= x;
        return result;
    }
    Vec<T, N> operator*(const Vec<T, N>& v) const {
        Vec<T, N> result{ 0 };
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                result[r] += data[r][c] * v[c];
        return result;
    }
    void operator*=(const TypeName& rhs) {
        *this = (*this) * rhs;
    }
    void operator*=(T x) {
        for (auto& it_row : data)
            for (auto& it : it_row)
                it *= x;
    }

    // basic linear transformations of matrix
    void Replace(int r0, int r1, T x) {
        for (int c = 0; c < N; c++)
            data[r0][c] += data[r1][c] * x;
    }
    void Interchange(int r0, int r1) {
        for (int c = 0; c < N; c++) {
            T tmp = data[r0][c];
            data[r0][c] = data[r1][c];
            data[r1][c] = tmp;
        }
    }
    void Scale(int r, T x) {
        for (auto& it : data[r])
            it *= x;
    }

    // det
    T Det() const {
        T det{ 1 };
        TypeName m{ *this };
        for (int r = 0; r < N - 1; r++) {
            int r_max{ r };
            for (int r_tmp = r + 1; r_tmp < N; r_tmp++)
                if (m.data[r_tmp][r] > m.data[r_max][r])
                    r_max = r_tmp;

            if (r_max != r) {
                det *= -1;
                m.Interchange(r, r_max);
            }

            for (int r1 = r + 1; r1 < N; r1++)
                m.Replace(r1, r, -m.data[r1][r] / m.data[r][r]);
        }
        for (int r = 0; r < N; r++)
            det *= data[r][r];
        return det;
    }

    // get inverse matrix
    TypeName Inv() const {
        TypeName m{ *this };
        TypeName result{ TypeName::UnitMat() };
        for (int r = 0; r < N - 1; r++) {
            // find row with the max data in column r from row r to row (N - 1)
            int r_max{ r };
            for (int r_tmp = r + 1; r_tmp < N; r_tmp++)
                if (abs(m.data[r_tmp][r]) > abs(m.data[r_max][r]))
                    r_max = r_tmp;

            if (r_max != r) {
                m.Interchange(r, r_max);
                result.Interchange(r, r_max);
            }

            for (int r1 = r + 1; r1 < N; r1++) {
                T tmp{ -m.data[r1][r] / m.data[r][r] };
                m.Replace(r1, r, tmp);
                result.Replace(r1, r, tmp);
            }
        }
        for (int r = N - 1; r > 0; r--)
            for (int r1 = r - 1; r1 >= 0; r1--) {
                T tmp{ -m.data[r1][r] / m.data[r][r] };
                //m.Replace(r1, r, tmp);
                result.Replace(r1, r, tmp);
            }
        for (int r = 0; r < N; r++) {
            result.Scale(r, 1 / m.data[r][r]);
        }
        return result;
    }

    // get transpose matrix
    TypeName Transpose() const {
        TypeName m{ 0 };
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                m[r][c] = (*this)[c][r];
        return m;
    }

    // static member functions to geenrate specific matrix
	static TypeName ConstMat(T x) {
        return TypeName{ x };
	}
	static TypeName ZeroMat() {
        return TypeName{ 0 };
	}
	static TypeName UnitMat() {
        TypeName result{ 0 };
        for (int r = 0; r < N; r++)
            result[r][r] = 1;
        return result;
	}
};
typedef Mat<float, 2> mat2;
typedef Mat<int, 2> imat2;
typedef Mat<unsigned, 2> uimat2;

typedef Mat<float, 3> mat3;
typedef Mat<int, 3> imat3;
typedef Mat<unsigned, 3> uimat3;

typedef Mat<float, 4> mat4;
typedef Mat<int, 4> imat4;
typedef Mat<unsigned, 4> uimat4;

vec4 homo(const vec4& v) {
    if (v[3] == 0)
        return v;
    else {
        return vec4{v[0] / v[3], v[1] / v[3], v[2] / v[3], 1.0f};
    }
}