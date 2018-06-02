#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

bool Graphics::Init(HWND windowHandle)
{
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), &factory))) return false;

	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &writeFactory))) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	if (FAILED(
		factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
			),
			D2D1::HwndRenderTargetProperties(
				windowHandle,
				D2D1::SizeU(rect.right, rect.bottom)
			),
			&renderTarget
		)
	)) return false;

	if (FAILED(renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush))) return false;

	if (FAILED(writeFactory->CreateTextFormat(
		  L"Meiryo"
		, NULL
		, DWRITE_FONT_WEIGHT_NORMAL
		, DWRITE_FONT_STYLE_NORMAL
		, DWRITE_FONT_STRETCH_NORMAL
		, 8
		, L""
		, &textFormat
	))) return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b, float a)
{
	renderTarget->Clear(D2D1::ColorF(r,g,b,a));
}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	auto rect = D2D1::RectF(x1, y1, x2, y2);
	renderTarget->FillRectangle(rect, brush.Get());
}

void Graphics::DrawCircle(D2D1_ELLIPSE ellipse, D2D1::ColorF color)
{
	brush->SetColor(color);
	renderTarget->DrawEllipse(ellipse, brush.Get());
}
void Graphics::DrawCircle(Point position, float radius, D2D1::ColorF color)
{
	DrawCircle(D2D1::Ellipse(D2D1::Point2F(position.x, position.y), radius, radius), color);
}
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{	
	DrawCircle(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), D2D1::ColorF(r, g, b, a));
}

void Graphics::DrawTextVTC(const std::string &text, Point position, D2D1::ColorF color)
{
	brush->SetColor(color);
	auto wstext = Utf8ToWString(text);
	auto size = renderTarget.Get()->GetSize();
	auto rect = D2D1::RectF(position.x-3, position.y-5, size.width, size.height);
	renderTarget->DrawText(
		  wstext.c_str()   // 文字列
		, wstext.size()    // 文字数
		, textFormat.Get()
		, rect
		, brush.Get()
		, D2D1_DRAW_TEXT_OPTIONS_NONE
	);
}

std::wstring Graphics::Utf8ToWString(std::string utf8Text)
{
	// バッファサイズの取得
	int iBufferSize = ::MultiByteToWideChar(CP_UTF8, 0, utf8Text.c_str()
		, -1, (wchar_t *)NULL, 0);

	// バッファの取得
	wchar_t* wpBufWString = (wchar_t*)new wchar_t[iBufferSize];

	// UTF8 → wstring
	::MultiByteToWideChar(CP_UTF8, 0, utf8Text.c_str(), -1, wpBufWString
		, iBufferSize);

	// wstringの生成
	std::wstring oRet(wpBufWString, wpBufWString + iBufferSize - 1);

	// バッファの破棄
	delete[] wpBufWString;

	// 変換結果を返す
	return(oRet);
}
