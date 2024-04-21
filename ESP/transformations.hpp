#pragma once
#include "vector3.hpp"
#include "vector2.hpp"
#include <windows.h>

struct matrix_t {
    float m[16];
};

vector3_t transform_coordinate(const vector3_t& coord, const matrix_t& matrix);

bool world_to_screen(HANDLE processHandle, uintptr_t gameBaseAddress, const vector3_t& world_coord, vector2_t& screen_coord, HWND hwnd);
