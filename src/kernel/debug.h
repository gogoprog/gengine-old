#pragma once

#include <iostream>

#ifdef DEBUG
#define geDebugLog(line) std::cout << "[gengine] " << line << std::endl;
#define geDebugLogN(line) std::cout << "[gengine] " << line;
#define geDebugRawLog(line) std::cout << line << std::endl;
#else
#define geDebugLog(line)
#define geDebugLogN(line)
#define geDebugRawLog(line)
#endif
