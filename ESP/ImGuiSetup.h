#pragma once
#include <windows.h>
#include <vector>
#include "vector3.hpp"

void InitializeImGui(HWND hwnd);
void CleanupImGui();
void RenderImGui(HWND hwnd, HANDLE processHandle, uintptr_t gameBaseAddress);