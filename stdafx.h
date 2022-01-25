#pragma once

#define _WIN32_WINNT 0x0602 

#pragma comment(lib,"d3d11.lib")
#include "targetver.h"
#include "tsf.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdint.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include <d3d11.h>
#include <dxgi1_2.h>