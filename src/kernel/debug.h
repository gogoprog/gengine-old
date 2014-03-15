#pragma once

#include <iostream>

#ifdef DEBUG
#define geLog(line) std::cout << "[gengine] " << line << std::endl;
#define geLogN(line) std::cout << "[gengine] " << line;
#define geRawLog(line) std::cout << line << std::endl;
#else
#define geLog(line)
#define geLogN(line)
#define geRawLog(line)
#endif
