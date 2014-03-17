#pragma once

#include "primitives.h"

struct lua_State;

namespace gengine
{
namespace script
{

class System
{
public:
    SINGLETON(System);
    void init();
    void finalize();
    void executeFile(const char * file);
    void call(const char * name);
    void call(const char * name, const float arg);

private:
    void internalCall(const uint arg_count);
    void handleError();

    lua_State
        * state;
};

}
}
