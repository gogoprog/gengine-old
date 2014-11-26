#pragma once

#include <vector>
#include <string>
#include <cstring>
#include "map.h"
#include "script.h"
#include "pointer.h"

#define MANAGER_DECLARE(_class_) \
    static SCRIPT_FUNCTION(create) \
    { \
        return getInstance().createItem(state); \
    } \
    static SCRIPT_FUNCTION(get) \
    { \
        return getInstance().getItem(state); \
    } \
    static SCRIPT_REGISTERER() \
    { \
        lua_newtable(state); \
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, create); \
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, get); \
        internalLuaRegister(state); \
    } \
    SINGLETON(_class_);

namespace gengine
{

template<class T>
class Manager
{
public:
    Manager() = default;

    void init()
    {
        internalInit();
    }

    void finalize()
    {
        for(auto & kv : itemMap)
        {
            kv.second->finalize();
            delete kv.second;
        }

        internalFinalize();
    }

protected:
    virtual bool internalCreate(T * t, script::State state, const int parameter_position) = 0;
    virtual void internalGetName(char * name, const char * arg) = 0;
    virtual void internalInit() {}
    virtual void internalFinalize() {}
    static void internalLuaRegister(script::State /*state*/) {}

    int createItem(script::State state, const int parameter_position = 1)
    {
        const char * arg = lua_tostring(state, parameter_position);
        char name[128];

        T * t = new T();

        t->init();

        if(internalCreate(t, state, parameter_position))
        {
            internalGetName(name, arg);
            itemMap.add(t, name);
            lua_pushlightuserdata(state, t);
        }
        else
        {
            if(defaultItem)
            {
                internalGetName(name, arg);
                itemMap.add(defaultItem, name);
            }

            t->finalize();
            delete t;
            lua_pushnil(state);
        }

        return 1;
    }

    int getItem(script::State state)
    {
        const char * name = lua_tostring(state, 1);
        T * t;

        if(itemMap.find(t, name))
        {
            lua_pushlightuserdata(state, t);
        }
        else
        {
            lua_pushnil(state);
        }

        return 1;
    }

    Map<std::string, T*>
        itemMap;
    Pointer<T>
        defaultItem;
};

}
