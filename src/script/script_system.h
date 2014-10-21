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
    void init2();
    void executeFile(const char * file);
    void executeText(const char * text);
    void call(const char * name);
    void call1(const char * name, const float arg);
    void call(const uint nargs, const uint nresults);

    lua_State * getState() { return state; }

private:
    static int traceBack(lua_State *state);

    lua_State
        * state;
};

}
}
