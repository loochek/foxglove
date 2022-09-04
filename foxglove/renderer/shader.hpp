#pragma once

#include <glad/glad.h>

#include <utils/common.hpp>
#include <utils/non_copyable.hpp>
#include <math/vector.hpp>
#include <math/matrix.hpp>
#include <renderer/gl_assert.hpp>
#include <renderer/shader_params.hpp>

namespace foxglove::renderer {
    /// GPU program abstraction
    class Shader : private foxglove::utils::NonCopyable {
    public:
        Shader(const char* vert_src, const char* frag_src);
        ~Shader();

        void SetUniform(const char* name, int value) const;
        void SetUniform(const char* name, const math::Vec2i& vector) const;
        void SetUniform(const char* name, const math::Vec3i& vector) const;
        void SetUniform(const char* name, const math::Vec4i& vector) const;

        void SetUniform(const char* name, float value) const;
        void SetUniform(const char* name, const math::Vec2f& vector) const;
        void SetUniform(const char* name, const math::Vec3f& vector) const;
        void SetUniform(const char* name, const math::Vec4f& vector) const;

        void SetUniform(const char* name, const math::Mat4f& matrix) const;

        void ApplyParamList(const ShaderParamList& list) const;

        void Bind() const {
            GL_ASSERT(glUseProgram(handle_));
        }

        static void Unbind() {
            GL_ASSERT(glUseProgram(0));
        }

    private:
        template<typename Func>
        void BindScope(Func func) const {
            Bind();
            func();
            Unbind();
            /// TODO: exception safety
        }

        static GLuint CompileShaderPart(const char* src, GLuint type);
        
    private:
        GLuint handle_;
    };
}
