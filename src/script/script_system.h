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
    bool executeFile(const char * file);
    bool executeText(const char * text);
    bool call(const char * name);
    bool call1(const char * name, const float arg);
    bool call(const uint nargs, const uint nresults);

    lua_State * getState() { return state; }

private:
    static int traceBack(lua_State *state);

    lua_State
        * state;
};

}
}
