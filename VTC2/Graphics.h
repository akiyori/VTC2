#pragma once

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include <wrl\client.h>
#include <string>
#include <iostream>
#include <locale> 
#include <codecvt>

#include "point.h"

using namespace Microsoft::WRL;

class Graphics
{
	ComPtr<ID2D1Factory> factory;
	ComPtr<ID2D1HwndRenderTarget> renderTarget;
	ComPtr<ID2D1SolidColorBrush> brush;
	ComPtr<IDWriteFactory> writeFactory;
	ComPtr<IDWriteTextFormat> textFormat;
	std::wstring Utf8ToWString(std::string utf8Text);
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b, float a);
	void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
	void FillRectangle(Point start, Point end, float r, float g, float b, float a);
	void DrawCircle(D2D1_ELLIPSE ellipse, D2D1::ColorF color);
	void DrawCircle(Point position, float radius, D2D1::ColorF color);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawTextVTC(const std::string &text, Point position, D2D1::ColorF color);
	void DrawTextFrameRate(double frameRate);
};