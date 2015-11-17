#include "graphics_spine_manager.h"

#include "debug.h"
#include "core_json.h"
#include <cstring>
#include <iostream>
#include <fstream>

namespace gengine
{
namespace graphics
{

bool SpineManager::internalCreate(SpineManagerItem * _item, script::State state, const int parameter_position)
{
    std::string path = lua_tostring(state, parameter_position);
    size_t pos = path.find_last_of(".");
    std::string base_name = path.substr(0, pos);
    std::string base_name_without_path = base_name;
    pos = path.find_last_of("/");

    if(pos != std::string::npos)
    {
        base_name_without_path = base_name_without_path.substr(pos + 1);
    }

    auto atlas = spAtlas_createFromFile((base_name + ".atlas").c_str(), 0);
    auto json = spSkeletonJson_create(atlas);
    auto skeletonData = spSkeletonJson_readSkeletonDataFile(json, path.c_str());
    auto animationStateData = spAnimationStateData_create(skeletonData);

    if(!skeletonData)
    {
        geLog("Error: " << json->error);
        return false;
    }

    for(int i=0; i<skeletonData->animationsCount; ++i)
    {
        auto animation = skeletonData->animations[i];
        std::string final_key;

        final_key = base_name_without_path + "-" + animation->name;

        SpineManagerItem * item = new SpineManagerItem();

        item->skeletonData = skeletonData;
        item->animationStateData = animationStateData;
        item->animation = animation;
        item->init();

        itemMap.add(item, final_key);

        geDebugLog("graphics::SpineManager loaded \"" << final_key << "\"");
    }

    spSkeletonJson_dispose(json);

    return false;
}

void SpineManager::internalGetName(char * result, const char * arg)
{
    strcpy(result, arg);
}

}
}
