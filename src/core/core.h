#pragma once

namespace gengine
{
namespace core
{

bool mustQuit();

void init();
void beginUpdate(const float dt);
void endUpdate(const float dt);

}
}
