#pragma once

#include "primitives.h"
#include "map.h"
#include "script.h"
#include "manager.h"
#include <string>
#include <Urho3D/Urho2D/Sprite2D.h>

namespace gengine
{
namespace graphics
{

class SpriteManager : public Manager<Urho3D::Sprite2D>
{

public:
    SpriteManager() = default;

    MANAGER_DECLARE(SpriteManager);

    static void simplifyName(char *result, const char *input);

private:
    virtual Urho3D::Sprite2D * internalCreate(script::State state, const int parameter_position) override;
    virtual void internalGetName(char * name, const char * arg) override;
    virtual void internalInit() override;
    virtual void internalFinalize() override;
};

}
}
