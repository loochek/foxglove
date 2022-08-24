#pragma once

#include <glad/glad.h>

#include <utils/common.hpp>
#include <utils/non_copyable.hpp>
#include <math/vector.hpp>
#include <math/matrix.hpp>
#include <renderer/gl_assert.hpp>

namespace foxglove::renderer {
    /// GPU program abstraction
    class Shader : private foxglove::utils::NonCopyable {
        friend class Renderer;

    public:
        Shader(const char* vert_src, const char* frag_src);
        ~Shader();

        void SetUniform(const char* name, const math::Vec3f& vector) const;
        void SetUniform(const char* name, const math::Mat4f& matrix) const;
        void SetUniform(const char* name, int value) const;

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
