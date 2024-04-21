#pragma once
#ifndef OVERLAY_RENDERER_H
#define OVERLAY_RENDERER_H

#include <windows.h>

// Initialize Direct2D and DirectWrite
bool InitializeDirect2D(HWND hwnd);

// Cleanup all resources
void CleanUp();

// Draw text overlay
void DrawTextOverlay(const wchar_t* text, float x, float y);

#endif // OVERLAY_RENDERER_H