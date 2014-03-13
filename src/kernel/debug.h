#pragma once

#include <iostream>

#ifdef DEBUG
#define geLog(line) std::cout << "[gengine] " << line << std::endl;
#else
#define geLog(line)
#endif
