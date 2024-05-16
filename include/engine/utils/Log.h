#ifndef LOG_H
#define LOG_H

#include <iostream>

#define LOG_INFO(x) std::cout << "[INFO] " << x << std::endl
#define LOG_WARNING(x) std::cout << "[WARNING] " << x << std::endl
#define LOG_ERROR(x) std::cerr << "[ERROR] " << x << std::endl

#endif // !LOG_H