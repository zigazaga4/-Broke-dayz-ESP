#include "ImGuiSetup.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Graphics.h"
#include "memory.hpp"
#include "offsets.hpp"
#include "transformations.hpp"
#include "vector3.hpp"
#include "GameData.hpp"  
#include "vector2.hpp"
#include <vector>

extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern ID3D11RenderTargetView* g_mainRenderTargetView;

void InitializeImGui(HWND hwnd) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);

    
    OutputDebugStringA("Initializing ImGui DirectX...\n");

    if (!ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext)) {
        OutputDebugStringA("Failed to initialize ImGui DirectX.\n");
    }
    else {
        OutputDebugStringA("ImGui DirectX initialized successfully.\n");
    }
}

void CleanupImGui() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void RenderImGui(HWND hwnd, HANDLE processHandle, uintptr_t gameBaseAddress) {
    size_t entityCount = memory::read_memory<size_t>(processHandle, gameBaseAddress + offsets::world::near_entity_table_size);
    uintptr_t entityListBase = memory::read_memory<uintptr_t>(processHandle, gameBaseAddress + offsets::world::near_entity_table);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (size_t i = 0; i < entityCount; i++) {
        uintptr_t entityAddress = memory::read_memory<uintptr_t>(processHandle, entityListBase + i * sizeof(uintptr_t));
        vector3_t entityPosition = get_entity_position(processHandle, entityAddress);

        vector2_t screenPos;
        if (world_to_screen(processHandle, gameBaseAddress, entityPosition, screenPos, hwnd)) {
            ImGui::SetNextWindowPos(ImVec2(screenPos.x, screenPos.y), ImGuiCond_Always);
            ImGui::Begin("EntityWindow", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text("Entity");
            ImGui::End();
        }
    }

    ImGui::Render();
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}