#ifndef GLOBAL_H
#define GLOBAL_H

#define _USE_MATH_DEFINES

#include <raylib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <deque>
#include <algorithm>
#include <cstdio>
#include <cstddef>
#include <ctime>
#include <cmath>
#include <cfloat>
#include <cctype>
#include <new>
#include <cstdlib>
#include <limits>
#include <utility>
#include <random>

using namespace std;

#ifdef __linux__
namespace XL {
    #include "X11/Xlib.h"
    #include "X11/Xutil.h"
}
#endif
#ifdef _WIN32
#include <windows.h>
#endif

#endif