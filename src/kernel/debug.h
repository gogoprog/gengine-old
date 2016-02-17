#pragma once

#include <iostream>

#define geLog(line) std::cout << "[gengine] " << line << std::endl;
#define geLogN(line) std::cout << "[gengine] " << line;
#define geRawLog(line) std::cout << line << std::endl;
#define geRawLogN(line) std::cout << line;

#ifdef DEBUG
#define geDebugLog(line) geLog(line)
#define geDebugLogN(line) geLogN(line)
#define geDebugRawLog(line) geRawLog(line)
#define geDebugRawLogN(line) geRawLogN(line)
#else
#define geDebugLog(line)
#define geDebugLogN(line)
#define geDebugRawLog(line)
#define geDebugRawLogN(line)
#endif
