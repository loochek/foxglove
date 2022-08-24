#pragma once

#include <glad/glad.h>

#ifdef FXG_DEBUG
#define GL_ASSERT(expr) { \
    expr; \
    GLenum __gl_error_code = glGetError(); \
    FXG_ASSERT(__gl_error_code == GL_NO_ERROR); \
}
#else
#define GL_ASSERT(expr) expr
#endif
