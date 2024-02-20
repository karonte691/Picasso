#pragma once

#ifndef OPEN_GL_ERROR_H
#define OPEN_GL_ERROR_H

#include <Glew/glew.h>
#include <PEngine/Logger/Logger.h>
#include <PEngine/PBuild.h>
#include <GL/gl.h>

inline bool CheckOpenGLError(const char *statement, const char *file, int line)
{
#if PICASSO_DEBUG_ENABLE
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        Picasso::Engine::Logger::Logger::Error("[OpenGL Error] %s, FILE %s, LINE %d: %u", statement, file, line, error);
        return false;
    }
#endif

    return true;
}

#define CHECK_GL_ERROR(statement)                         \
    do                                                    \
    {                                                     \
        statement;                                        \
        CheckOpenGLError(#statement, __FILE__, __LINE__); \
    } while (0)

#endif