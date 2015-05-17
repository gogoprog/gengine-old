#include "graphics_spriter_manager.h"

#include "debug.h"
#include "core_json.h"
#include <cstring>
#include <iostream>
#include <fstream> 

namespace gengine
{
namespace graphics
{

SCRIPT_CLASS_FUNCTION(SpriterManager, loadFile)
{
    const char * path = lua_tostring(state, 1);

    std::filebuf fb;

    if (fb.open (path, std::ios::in))
    {
        core::Json json;
        std::istream istream(&fb);

        if(json.parse(istream))
        {
            SpriterFile & file = * new SpriterFile();

            file.load(json);

            getInstance().files.add( & file );

            for(const SpriterEntity & entity : file.entities)
            {
                for(const SpriterAnimation & animation : entity.animations)
                {
                    std::string final_key;

                    final_key = entity.name + "-" + animation.name;

                    SpriterManagerItem * item = new SpriterManagerItem();

                    item->init();
                    item->entity = & entity;
                    item->animation = & animation;

                    getInstance().itemMap.add(item, final_key);

                    geDebugLog("graphics::SpriterManager loaded \"" << final_key << "\" ... ");
                }
            }
        }
    }

    return 0;
}

bool SpriterManager::internalCreate(SpriterManagerItem * item, script::State state, const int parameter_position)
{
    return false;
}

void SpriterManager::internalGetName(char * result, const char * arg)
{
    strcpy(result, arg);
}

void SpriterManager::internalLuaRegister(script::State state)
{
    SCRIPT_TABLE_PUSH_CLASS_FUNCTION(SpriterManager, loadFile);
}

}
}
