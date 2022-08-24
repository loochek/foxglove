#include "shader.hpp"

#include <string>
#include <iostream>
#include <fmt/core.h>

namespace foxglove::renderer {
    Shader::Shader(const char* vs_src, const char* fs_src) {
        GLuint vertex_shader   = 0;
        GLuint fragment_shader = 0;
        GLuint shader_program = 0;

        try {
            vertex_shader   = CompileShaderPart(vs_src, GL_VERTEX_SHADER);
            fragment_shader = CompileShaderPart(fs_src, GL_FRAGMENT_SHADER);
        } catch (...) {
            GL_ASSERT(glDeleteShader(vertex_shader));
            GL_ASSERT(glDeleteShader(fragment_shader));
            throw;
        }
            
        GL_ASSERT(shader_program = glCreateProgram());
        GL_ASSERT(glAttachShader(shader_program, vertex_shader));
        GL_ASSERT(glAttachShader(shader_program, fragment_shader));
        GL_ASSERT(glLinkProgram(shader_program));

        GLint success = 0;
        GL_ASSERT(glGetProgramiv(shader_program, GL_LINK_STATUS, &success));
        if (!success) {
            GLint log_length = 0;
            GL_ASSERT(glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length));

            std::string link_log;
            link_log.resize(log_length);

            GL_ASSERT(glGetProgramInfoLog(shader_program, log_length, NULL, link_log.data()));

            GL_ASSERT(glDeleteProgram(shader_program));
            GL_ASSERT(glDeleteShader(vertex_shader));
            GL_ASSERT(glDeleteShader(vertex_shader));
            throw std::runtime_error(fmt::format("Shader link error: {}", link_log));
        }

        handle_ = shader_program;
    }

    Shader::~Shader() {
        GL_ASSERT(glDeleteProgram(handle_));
    }

    void Shader::SetUniform(const char* name, const math::Vec3f& vector) const {
        BindScope([&]() {
            GLuint location = glGetUniformLocation(handle_, name);
            GL_ASSERT((void)true);
            GL_ASSERT(glUniform3fv(location, 3, static_cast<const GLfloat*>(vector.RawData())));
        });
    }

    void Shader::SetUniform(const char* name, const math::Mat4f& matrix) const {
        BindScope([&]() {
            GLuint location = glGetUniformLocation(handle_, name);
            GL_ASSERT((void)true);
            GL_ASSERT(glUniformMatrix4fv(location, 1, true, static_cast<const GLfloat*>(matrix.RawData())));
        });
    }

    void Shader::SetUniform(const char *name, int value) const {
        BindScope([&]() {
            GLuint location = glGetUniformLocation(handle_, name);
            GL_ASSERT((void)true);
            GL_ASSERT(glUniform1i(location, value));
        });
    }

    GLuint Shader::CompileShaderPart(const char* src, GLuint type) {
        GLuint shader = 0;
        GL_ASSERT(shader = glCreateShader(type));

        GL_ASSERT(glShaderSource(shader, 1, &src, NULL));
        GL_ASSERT(glCompileShader(shader));

        GLint success = 0;
        GL_ASSERT(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
        if (!success) {
            GLint log_length = 0;
            GL_ASSERT(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length));

            std::string compile_log;
            compile_log.resize(log_length);

            GL_ASSERT(glGetShaderInfoLog(shader, log_length, NULL, compile_log.data()));

            GL_ASSERT(glDeleteShader(shader));
            throw std::runtime_error(fmt::format("Shader compilation error: {}", compile_log));
        }

        return shader;
    }
}
