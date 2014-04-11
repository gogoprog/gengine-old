#pragma once

namespace gengine
{
namespace core
{

bool mustQuit();

void init(int argc, char *argv[]);
void finalize();
void update();

}
}
