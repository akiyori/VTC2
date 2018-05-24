#pragma once

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <wrl\client.h>
using namespace Microsoft::WRL;

class Graphics
{
	ComPtr<ID2D1Factory> factory;
	ComPtr<ID2D1HwndRenderTarget> renderTarget;
	ComPtr<ID2D1SolidColorBrush> brush;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b, float a);
	void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);

};