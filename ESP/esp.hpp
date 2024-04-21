#pragma once
#include "memory.hpp"
#include "offsets.hpp"

void initializeESP(HANDLE process, uintptr_t baseAddress);
void updateESP();
void drawESP();