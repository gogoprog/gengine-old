#pragma once

#include <iostream>

#define geLog(line) std::cout << "[gengine] " << line << std::endl;
#define geLogN(line) std::cout << "[gengine] " << line;
#define geRawLog(line) std::cout << line << std::endl;

#ifdef DEBUG
#define geDebugLog(line) geLog(line)
#define geDebugLogN(line) geLogN(line)
#define geDebugRawLog(line) geRawLog(line)
#else
#define geDebugLog(line)
#define geDebugLogN(line)
#define geDebugRawLog(line)
#endif


