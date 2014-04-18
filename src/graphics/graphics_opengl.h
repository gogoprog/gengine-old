#pragma once

#ifdef _WINDOWS
	#include <windows.h>
#endif

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#ifdef DEBUG
#define GL_CHECK() \
    {\
        GLuint error_code; \
        error_code = glGetError(); \
        if(error_code != GL_NO_ERROR) \
        { \
            geDebugLog("OpenGL error!" ); \
            printf(" %s:%i code:0x%x\n", __FILE__, __LINE__, error_code); \
        }\
    }
#else
#define GL_CHECK()
#endif

#define GL_NULL_ID 0xffffffff

#ifdef EMSCRIPTEN
#define GL_GLSL(src) \
    #src
#else
#define GL_GLSL(src) \
    "#define highp \n#define mediump \n#define lowp \n" #src
#endif
