#pragma once

#include <vector>

#define SINGLETON(_class_name_) \
    static _class_name_ & getInstance() \
    {\
        static _class_name_ instance;\
        return instance;\
    }

typedef unsigned int uint;

typedef unsigned char uint8;
typedef signed char int8;

typedef unsigned short ushort;
