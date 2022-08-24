#pragma once

#include <utils/common.hpp>
#include <math/vector.hpp>

namespace foxglove::math {
    template <typename T>
    struct Mat4 {
    public:
        Mat4() {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] = (i == j) ? 1 : 0;
                }
            }
        }

        explicit Mat4(const T (&array)[4][4]) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] = array[i][j];
                }
            }
        }

        template<typename U>
        explicit Mat4(const Mat4<U>& other) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        template <typename U>
        Mat4 operator=(const Mat4<U>& other) {
            if (this != &other)
                Mat4(other).Swap(*this);
                
            return *this;
        }

        Mat4 operator+(const Mat4& other) const {
            Mat4 tmp(*this);
            tmp += other;
            return tmp;
        }

        Mat4 operator-(const Mat4& other) const {
            Mat4 tmp(*this);
            tmp -= other;
            return tmp;
        }

        Mat4 operator/(T divider) const
        {
            Mat4 tmp(*this);
            tmp /= divider;
            return tmp;
        }

        Mat4& operator+=(const Mat4& other)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] += other.data[i][j];
                }
            }

            return *this;
        }

        Mat4& operator-=(const Mat4& other)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] -= other.data[i][j];
                }
            }

            return *this;
        }

        Mat4& operator*=(T multiplier)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] *= multiplier;
                }
            }

            return *this;
        }

        Mat4& operator/=(T divider)
        {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    data[i][j] /= divider;
                }
            }

            return *this;
        }

        Mat4 operator*(const Mat4& other)
        {
            Mat4 result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 4; k++) {
                        result[i][j] += data[i][k] * other.data[k][j];
                    }
                }
            }

            return result;
        }

        Vec4<T> operator*(const Vec4<T>& vector)
        {
            Vec4<T> result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    result[i] += data[i][j] * vector[j];
                }
            }

            return result;
        }

        void Swap(Mat4& other) {
            std::swap(data, other.data);
        }

        const void* RawData() const {
            return reinterpret_cast<const void*>(data);
        }
        
    public:
        T data[4][4];
    };

    template<typename T>
    inline Mat4<T> operator*(const Mat4<T>& matrix, T multiplier)
    {
        Mat4<T> tmp(matrix);
        tmp *= multiplier;
        return tmp;
    }

    using Mat4f = Mat4<float>;
    using Mat4i = Mat4<int>;
}
