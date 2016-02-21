#pragma once

#include "application_window.h"

namespace gengine
{
namespace core
{

bool mustQuit();
application::Window getMainWindow();

bool init(int argc, char *argv[]);
int run();
void finalize();
void update();
void setMustQuit(const bool it_must_quit);
void setUpdateFactor(const float factor);

}
}
