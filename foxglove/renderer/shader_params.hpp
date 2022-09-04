#pragma once

#include <string>
#include <math/vector.hpp>
#include <math/matrix.hpp>

namespace foxglove::renderer {
    enum class ShaderParamType {
        Empty,

        Int,
        Vec2i,
        Vec3i,
        Vec4i,

        Float,
        Vec2f,
        Vec3f,
        Vec4f,

        Mat4f
    };

    struct ShaderParam {
        ShaderParamType type;

        ShaderParam() : type(ShaderParamType::Empty) {}

        ShaderParam(int param) : type(ShaderParamType::Int), param_Int(param) {}
        ShaderParam(math::Vec2i param) : type(ShaderParamType::Vec2i), param_Vec2i(param) {}
        ShaderParam(math::Vec3i param) : type(ShaderParamType::Vec3i), param_Vec3i(param) {}
        ShaderParam(math::Vec4i param) : type(ShaderParamType::Vec4i), param_Vec4i(param) {}

        ShaderParam(float param) : type(ShaderParamType::Float), param_Float(param) {}
        ShaderParam(math::Vec2f param) : type(ShaderParamType::Vec2f), param_Vec2f(param) {}
        ShaderParam(math::Vec3f param) : type(ShaderParamType::Vec3f), param_Vec3f(param) {}
        ShaderParam(math::Vec4f param) : type(ShaderParamType::Vec4f), param_Vec4f(param) {}

        ShaderParam(math::Mat4f param) : type(ShaderParamType::Mat4f), param_Mat4f(param) {}

        union {
            int param_Int;
            math::Vec2i param_Vec2i;
            math::Vec3i param_Vec3i;
            math::Vec4i param_Vec4i;

            float param_Float;
            math::Vec2f param_Vec2f;
            math::Vec3f param_Vec3f;
            math::Vec4f param_Vec4f;

            math::Mat4f param_Mat4f;
        };
    };

    class ShaderParamList {
    public:
        ShaderParamList() = default;
        ShaderParamList(const ShaderParamList& other) = default;
        ShaderParamList(ShaderParamList&& other) = default;

        void SetParam(const std::string& name, ShaderParam param) {
            FXG_ASSERT(param.type != ShaderParamType::Empty);
            params_[name] = param;
        }

        void Merge(ShaderParamList& other) {
            params_.merge(other.params_);
        }

        auto& GetParams() const {
            return params_;
        }

    private:
        std::unordered_map<std::string, ShaderParam> params_;
    };
}