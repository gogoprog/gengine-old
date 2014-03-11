#pragma once


#ifdef DEBUG
#define geLog(line) puts("[gengine] " line)
#else
#define geLog(line)
#endif