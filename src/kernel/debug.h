#pragma once

#include <cstdio>

#ifdef DEBUG
#define geLog(line) puts("[gengine] " line)
#else
#define geLog(line)
#endif