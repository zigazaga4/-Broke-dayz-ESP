#pragma once
#include "vector3.hpp"
#include <windows.h>
#include <vector>

std::vector<vector3_t> get_all_entities(HANDLE processHandle, uintptr_t gameBaseAddress);