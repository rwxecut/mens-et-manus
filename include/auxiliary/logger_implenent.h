#pragma once

#define LOG_FILENAME "log.txt"
#define LOG_IMPLEMENT
#include "Logger.h"
Logger logger (LOG_FILENAME);
#undef LOG_IMPLEMENT
