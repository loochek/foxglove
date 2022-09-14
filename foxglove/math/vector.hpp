#pragma once

#include <cmath>
#include <algorithm>
#include <utils/assert.hpp>

namespace foxglove::math {
    template <typename T>
    struct Vec2 {
    public:
        Vec2() : x(0), y(0) {}
        Vec2(T x, T y) : x(x), y(y) {}

        template <typename U>
        Vec2(const Vec2<U>& other) : x(other.x), y(other.y) {}

        template <typename U>
        Vec2 operator=(const Vec2<U>& other) {
            if (this != &other)
                Vec2(other).Swap(*this);

            return *this;
        }

        T& operator[](int component) {
            switch (component) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                FXG_ASSERT(false);
            }
        }

        const T& operator[](int component) const {
            return const_cast<const T&>(const_cast<Vec2*>(this)->operator[](component));
        }

        Vec2 operator+(const Vec2& other) const {
            Vec2 tmp(*this);
            tmp += other;
            return tmp;
        }

        Vec2 operator-() const {
            return Vec2(-x, -y);
        }

        Vec2 operator-(const Vec2& other) const {
            Vec2 tmp(*this);
            tmp -= other;
            return tmp;
        }

        Vec2 operator/(T divider) const
        {
            Vec2 tmp(*this);
            tmp /= divider;
            return tmp;
        }

        // Scalar multiplication
        T operator*(const Vec2& other) const
        {
            return x * other.x + y * other.y;
        }

        Vec2 Normalized() const
        {
            if (x == 0 && y == 0)
                return Vec2();

            double len = Length();
            return *this / len;
        }

        T Length() const
        {
            return sqrt(*this * *this);
        }

        Vec2 Reflected(Vec2 normal) const
        {
            return *this - (T(2) * (*this * normal)) * normal;
        }

        Vec2& operator+=(const Vec2& other)
        {
            x += other.x;
            y += other.y;

            return *this;
        }

        Vec2& operator-=(const Vec2& other)
        {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        Vec2& operator*=(T multiplier)
        {
            x *= multiplier;
            y *= multiplier;

            return *this;
        }

        Vec2& operator/=(T divider)
        {
            x /= divider;
            y /= divider;

            return *this;
        }

        void Swap(const Vec2& other) {
            std::swap(x, other.x);
            std::swap(y, other.y);
        }

        const void* RawData() const {
            return reinterpret_cast<const void*>(this);
        }

    public:
        T x, y;
    };

    template<typename T>
    inline Vec2<T> operator*(const Vec2<T>& vector, T multiplier)
    {
        Vec2<T> tmp(vector);
        tmp *= multiplier;
        return tmp;
    }

    using Vec2f = Vec2<float>;
    using Vec2i = Vec2<int>;

    template <typename T>
    struct Vec3 {
    public:
        Vec3() : x(0), y(0), z(0) {}
        Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

        template <typename U>
        Vec3(const Vec3<U>& other) : x(other.x), y(other.y), z(other.z) {}

        template <typename U>
        Vec3(const Vec2<U>& other, U z) : x(other.x), y(other.y), z(z) {}

        template <typename U>
        Vec3 operator=(const Vec3<U>& other) {
            if (this != &other)
                Vec3(other).Swap(*this);
                
            return *this;
        }

        T& operator[](int component) {
            switch (component) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                FXG_ASSERT(false);
            }
        }

        const T& operator[](int component) const {
            return const_cast<const T&>(const_cast<Vec3*>(this)->operator[](component));
        }

        Vec3 operator+(const Vec3& other) const {
            Vec3 tmp(*this);
            tmp += other;
            return tmp;
        }

        Vec3 operator-() const {
            return Vec3(-x, -y, -z);
        }

        Vec3 operator-(const Vec3& other) const {
            Vec3 tmp(*this);
            tmp -= other;
            return tmp;
        }

        Vec3 operator*(T multiplier) const
        {
            Vec3 tmp(*this);
            tmp *= multiplier;
            return tmp;
        }

        Vec3 operator/(T divider) const
        {
            Vec3 tmp(*this);
            tmp /= divider;
            return tmp;
        }

        // Scalar multiplication
        T operator*(const Vec3& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        /// Vector multiplication
        Vec3 operator^(const Vec3& other) const
        {
            return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }

        Vec3 Normalized() const
        {
            if (x == 0 && y == 0 && z == 0)
                return Vec3();

            double len = Length();
            return *this / len;
        }

        T Length() const
        {
            return sqrt(*this * *this);
        }

        Vec3 Reflected(Vec3 normal) const
        {
            return *this - (T(2) * (*this ^ normal)) * normal;
        }

        Vec3& operator+=(const Vec3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }

        Vec3& operator-=(const Vec3& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;

            return *this;
        }

        Vec3& operator*=(T multiplier)
        {
            x *= multiplier;
            y *= multiplier;
            z *= multiplier;

            return *this;
        }

        Vec3& operator/=(T divider)
        {
            x /= divider;
            y /= divider;
            z /= divider;

            return *this;
        }

        void Swap(const Vec3& other) {
            std::swap(x, other.x);
            std::swap(y, other.y);
            std::swap(z, other.z);
        }

        const void* RawData() const {
            return reinterpret_cast<const void*>(this);
        }

    public:
        T x, y, z;
    };
    
    template<typename T>
    inline Vec3<T> operator*(const Vec3<T>& vector, T multiplier)
    {
        Vec3<T> tmp(vector);
        tmp *= multiplier;
        return tmp;
    }

    using Vec3f = Vec3<float>;
    using Vec3i = Vec3<int>;

    template <typename T>
    struct Vec4 {
    public:
        Vec4() : x(0), y(0), z(0), w(0) {}
        Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

        template <typename U>
        Vec4(const Vec4<U>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

        template <typename U>
        Vec4(const Vec3<U>& other, U w = 1) : x(other.x), y(other.y), z(other.z), w(w) {}

        template <typename U>
        Vec4 operator=(const Vec4<U>& other) {
            if (this != &other)
                Vec4(other).Swap(*this);
                
            return *this;
        }

        T& operator[](int component) {
            switch (component) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                FXG_ASSERT(false);
            }
        }

        const T& operator[](int component) const {
            return const_cast<const T&>(const_cast<Vec4*>(this)->operator[](component));
        }

        Vec4 operator+(const Vec4& other) const {
            Vec4 tmp(*this);
            tmp += other;
            return tmp;
        }

        Vec4 operator-() const {
            return Vec4(-x, -y, -z, -w);
        }

        Vec4 operator-(const Vec4& other) const {
            Vec4 tmp(*this);
            tmp -= other;
            return tmp;
        }

        Vec4 operator*(T multiplier) const
        {
            Vec4 tmp(*this);
            tmp *= multiplier;
            return tmp;
        }

        Vec4 operator/(T divider) const
        {
            Vec4 tmp(*this);
            tmp /= divider;
            return tmp;
        }

        // Scalar multiplication
        T operator*(const Vec4& other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        Vec4& operator+=(const Vec4& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;

            return *this;
        }

        Vec4& operator-=(const Vec4& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;

            return *this;
        }

        Vec4& operator*=(T multiplier)
        {
            x *= multiplier;
            y *= multiplier;
            z *= multiplier;
            w *= multiplier;

            return *this;
        }

        Vec4& operator/=(T divider)
        {
            x /= divider;
            y /= divider;
            z /= divider;
            w /= divider;

            return *this;
        }

        void Swap(const Vec4& other) {
            std::swap(x, other.x);
            std::swap(y, other.y);
            std::swap(z, other.z);
            std::swap(w, other.w);
        }

        const void* RawData() const {
            return reinterpret_cast<const void*>(this);
        }

    public:
        T x, y, z, w;
    };
    
    template<typename T>
    inline Vec4<T> operator*(const Vec4<T>& vector, T multiplier)
    {
        Vec4<T> tmp(vector);
        tmp *= multiplier;
        return tmp;
    }

    using Vec4f = Vec4<float>;
    using Vec4i = Vec4<int>;
};
