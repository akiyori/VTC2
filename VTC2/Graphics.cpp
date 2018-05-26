#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

bool Graphics::Init(HWND windowHandle)
{
	if(FAILED(D2D1CreateFactory<ID2D1Factory>(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory))) return false;

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

	if (FAILED(renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush))) return false;;
	
	return true;
}

void Graphics::ClearScreen(float r, float g, float b, float a)
{
	renderTarget->Clear(D2D1::ColorF(r,g,b,a));
}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::RectF(x1, y1, x2, y2);
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