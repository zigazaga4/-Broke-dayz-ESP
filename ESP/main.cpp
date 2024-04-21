#include <windows.h>
#include <iostream>
#include "memory.hpp"  
#include "offsets.hpp" 
#include "Graphics.h"  
#include "ImGuiSetup.h"  
#include "GameData.hpp"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // Register window class
    const wchar_t CLASS_NAME[] = L"ESPOverlayWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_DROPSHADOW | CS_VREDRAW | CS_HREDRAW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Create window
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT, 
        CLASS_NAME,                                        
        L"DayZ ESP Overlay",                               
        WS_POPUP,                                          
        0, 0,                                              
        GetSystemMetrics(SM_CXSCREEN),                     
        GetSystemMetrics(SM_CYSCREEN),                     
        NULL,                                              
        NULL,                                              
        hInstance,                                         
        NULL                                               
    );

    // Set window transparency
    SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);

    // Show window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    std::cout << "Starting DayZ ESP Mod...\n";

    DWORD processId = memory::get_process_id("DayZ_x64.exe");
    if (processId == 0) {
        std::cerr << "Failed to find DayZ process.\n";
        return 1;
    }

    HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);
    if (!processHandle) {
        std::cerr << "Failed to open DayZ process.\n";
        return 1;
    }

    uintptr_t gameBaseAddress = memory::get_module_base_address(processId, "DayZ_x64.exe");
    if (gameBaseAddress == 0) {
        std::cerr << "Failed to find the base address of DayZ.\n";
        CloseHandle(processHandle);
        return 1;
    }

    if (!InitializeDirectX(hwnd)) {
        std::cerr << "Failed to initialize DirectX.\n";
        CloseHandle(processHandle);
        return 1;
    }

    InitializeImGui(hwnd);

    // Main message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CleanupImGui();
    CleanupDirectX();
    CloseHandle(processHandle);
    std::cout << "Shutting down DayZ ESP Mod.\n";
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}