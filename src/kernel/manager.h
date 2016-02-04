#pragma once

#include <vector>
#include <string>
#include <cstring>
#include "map.h"
#include "script.h"
#include "pointer.h"
#include "debug.h"
#include <cstring>
#include <dirent.h>

#define MANAGER_DECLARE(_class_) \
    static SCRIPT_FUNCTION(create) \
    { \
        return getInstance().createItem(state); \
    } \
    static SCRIPT_FUNCTION(createFromDirectory) \
    { \
        return getInstance().createFromDirectory(state); \
    } \
    static SCRIPT_FUNCTION(get) \
    { \
        return getInstance().getItem(state); \
    } \
    static SCRIPT_FUNCTION(getKeys) \
    { \
        return getInstance().getKeys(state); \
    } \
    static SCRIPT_REGISTERER() \
    { \
        lua_newtable(state); \
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, create); \
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, createFromDirectory); \
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, get); \
        SCRIPT_TABLE_PUSH_CLASS_FUNCTION(_class_, getKeys); \
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

    void init(const char * item_type_name)
    {
        itemTypeName = item_type_name;
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

    T * getItem(const char * name)
    {
        T * t;

        if(itemMap.find(t, name))
        {
            return t;
        }
        else
        {
            geLog("Cannot find " << itemTypeName << " \"" << name << "\"");

            if(defaultItem)
            {
                return defaultItem;
            }
        }

        return nullptr;
    }

    void addSupportedExtension(const char * extension)
    {
        supportedExtensions.add(true, extension);
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
        internalGetName(name, arg);

        if(itemMap.contains(name))
        {
            geDebugLog("Skipping already loaded " << itemTypeName << " '" << name << "'");
            lua_pushlightuserdata(state, itemMap[name]);
            return 1;
        }

        T * t = new T();

        t->init();

        if(internalCreate(t, state, parameter_position))
        {
            itemMap.add(t, name);
            lua_pushlightuserdata(state, t);
        }
        else
        {
            if(defaultItem)
            {
                itemMap.add(defaultItem, name);
            }

            t->finalize();
            delete t;
            lua_pushnil(state);
        }

        return 1;
    }

    int createFromDirectory(script::State state)
    {
        const char * path = lua_tostring(state, 1);
        DIR * directory;
        dirent * result;

        directory = opendir(path);

        if(directory)
        {
            while((result = readdir(directory)))
            {
                std::string str_name = result->d_name;
                size_t length = str_name.length();

                if(length > 4)
                {
                    size_t pos = str_name.find_last_of(".");
                    if(pos != std::string::npos)
                    {
                        std::string extension = str_name.substr(pos);

                        if(supportedExtensions.contains(extension))
                        {
                            std::string final_path = path;
                            final_path += "/";
                            final_path += str_name;

                            lua_pushstring(state, final_path.c_str());
                            createItem(state, -1);
                            lua_pop(state, 1);
                        }
                    }
                }
            }

            closedir(directory);
        }

        return 0;
    }

    int getItem(script::State state)
    {
        const char * name = lua_tostring(state, 1);
        auto item = getItem(name);

        if(item)
        {
            lua_pushlightuserdata(state, item);
        }
        else
        {
            lua_pushnil(state);
        }

        return 1;
    }

    int getKeys(script::State state) const
    {
        int i = 0;

        lua_newtable(state);

        for(auto & item : itemMap)
        {
            lua_pushstring(state, item.first.c_str());
            lua_rawseti(state, -2, ++i);
        }

        return 1;
    }

    Map<std::string, T*>
        itemMap;
    Pointer<T>
        defaultItem;
    std::string
        itemTypeName;
    Map<std::string, bool>
        supportedExtensions;
};

}
