#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>


#define GL_CHECK() \
    {\
        GLuint error_code; \
        error_code = glGetError(); \
        if(error_code != GL_NO_ERROR) \
        { \
            geLog("OpenGL error!"); \
        }\
    }
