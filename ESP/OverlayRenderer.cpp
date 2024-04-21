#include "OverlayRenderer.h"
#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

ID2D1Factory* pD2DFactory = NULL;
IDWriteFactory* pDWriteFactory = NULL;
ID2D1HwndRenderTarget* pRenderTarget = NULL;
IDWriteTextFormat* pTextFormat = NULL;
ID2D1SolidColorBrush* pBrush = NULL;

// Initialization function
bool InitializeDirect2D(HWND hwnd) {
    // Create D2D factory
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    if (!SUCCEEDED(hr)) return false;

    // Create DirectWrite factory
    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
    if (!SUCCEEDED(hr)) return false;

    // Create render target
    hr = pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(800, 600)),
        &pRenderTarget);
    if (!SUCCEEDED(hr)) return false;

    // Create a brush
    hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
    if (!SUCCEEDED(hr)) return false;

    // Create text format
    hr = pDWriteFactory->CreateTextFormat(
        L"Verdana",
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        24,
        L"", //locale
        &pTextFormat);
    return SUCCEEDED(hr);
}

void CleanUp() {
    if (pBrush) pBrush->Release();
    if (pRenderTarget) pRenderTarget->Release();
    if (pTextFormat) pTextFormat->Release();
    if (pDWriteFactory) pDWriteFactory->Release();
    if (pD2DFactory) pD2DFactory->Release();
}

// Drawing function
void DrawTextOverlay(const wchar_t* text, float x, float y) {
    pRenderTarget->BeginDraw();
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black, 0.0f)); // Transparent background
    pRenderTarget->DrawText(
        text,
        wcslen(text),
        pTextFormat,
        D2D1::RectF(x, y, x + 300, y + 50),
        pBrush);
    HRESULT hr = pRenderTarget->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
        CleanUp();  // Handle device lost, recreate render target
        InitializeDirect2D(GetHWND());  // Assuming you have access to the current HWND
    }
}