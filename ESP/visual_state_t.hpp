#pragma once

#ifndef VISUAL_STATE_T_HPP
#define VISUAL_STATE_T_HPP

#include "memory.hpp"   // Make sure this path is correct and accessible
#include "vector3.hpp"  // Ensures the vector3_t structure is available
#include "offsets.hpp"  // Contains all the game-specific offsets

struct matrix_t {
    float m[16];
};

class visual_state_t {
public:
    uintptr_t base_address;

    visual_state_t(uintptr_t addr) : base_address(addr) {}

    vector3_t position(HANDLE processHandle) {
        return memory::read_memory<vector3_t>(processHandle, base_address + offsets::visual_state::position);
    }

    matrix_t matrix(HANDLE processHandle) {
        return memory::read_memory<matrix_t>(processHandle, base_address + offsets::visual_state::matrix);
    }
};

#endif // VISUAL_STATE_T_HPP