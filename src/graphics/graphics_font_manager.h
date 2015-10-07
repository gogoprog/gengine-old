#pragma once

#include "primitives.h"
#include "manager.h"
#include "graphics_font.h"

namespace gengine
{
namespace graphics
{

class FontManager : public Manager<Font>
{

public:
    FontManager() = default;

    MANAGER_DECLARE(FontManager);

private:
    virtual bool internalCreate(Font * font, script::State state, const int parameter_position) override;
    virtual void internalGetName(char * name, const char * arg) override;
    virtual void internalInit() override;
    virtual void internalFinalize() override;
};

}
}
