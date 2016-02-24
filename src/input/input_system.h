#pragma once

#include "primitives.h"
#include "array.h"
#include "maths.h"
#include "core.h"

namespace gengine
{
namespace input
{

class System
{
public:
    SINGLETON(System);

    void init();
    void finalize();
    void update();

    void setMouseVisible(const bool visible)
    {
        input->SetMouseVisible(visible);
    }

    inline bool isKeyUp(const int key) const
    {
        return !input->GetScancodeDown(key);
    }

    inline bool isKeyDown(const int key) const
    {
        return input->GetScancodeDown(key);
    }

    inline bool isKeyJustDown(const int key) const
    {
        return input->GetScancodePress(key);
    }

    inline bool isMouseButtonDown(const int button) const
    {
        return input->GetMouseButtonDown(SDL_BUTTON(button));
    }

    inline bool isMouseButtonUp(const int button) const
    {
        return !input->GetMouseButtonDown(SDL_BUTTON(button));
    }

    inline bool isMouseButtonJustDown(const int button) const
    {
        return input->GetMouseButtonPress(SDL_BUTTON(button));
    }

    inline math::Vector2 getMousePosition() const
    {
        auto v = input->GetMousePosition();
        return math::Vector2(v.x_, v.y_);
    }

private:
    Urho3D::Input
        *input;
};

}
}
