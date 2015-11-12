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

bool SpriterManager::internalCreate(SpriterManagerItem * _item, script::State state, const int parameter_position)
{
    const char * path = lua_tostring(state, parameter_position);

    std::filebuf fb;

    if (fb.open (path, std::ios::in))
    {
        core::Json json;
        std::istream istream(&fb);

        if(json.parse(istream))
        {
            SpriterFile & file = * new SpriterFile();

            file.load(json);

            files.add( & file );

            for(const SpriterEntity & entity : file.entities)
            {
                for(const SpriterAnimation & animation : entity.animations)
                {
                    std::string final_key;

                    final_key = entity.name + "-" + animation.name;

                    SpriterManagerItem * item = new SpriterManagerItem();

                    item->entity = & entity;
                    item->animation = & animation;
                    item->init();

                    itemMap.add(item, final_key);

                    geDebugLog("graphics::SpriterManager loaded \"" << final_key << "\" " << (animation.looping ? "(loop)" : "") << "...");
                }
            }
        }
    }

    return false;
}

void SpriterManager::internalGetName(char * result, const char * arg)
{
    strcpy(result, arg);
}

}
}
