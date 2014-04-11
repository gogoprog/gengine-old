#pragma once

#include "application_window.h"

namespace gengine
{
namespace core
{

bool mustQuit();
application::Window getMainWindow();

void init(int argc, char *argv[]);
void finalize();
void update();

}
}
