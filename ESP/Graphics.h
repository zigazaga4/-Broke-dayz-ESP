#pragma once
#include <d3d11.h>
#include <windows.h>
#include <dxgi.h>
#include <dxgi1_2.h>

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern ID3D11RenderTargetView* g_mainRenderTargetView;
extern IDXGISwapChain* g_pSwapChain;

bool InitializeDirectX(HWND hwnd);
void CleanupDirectX();