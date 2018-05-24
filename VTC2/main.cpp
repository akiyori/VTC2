#include <windows.h>
#include <tchar.h>

#include "graphics.h"

#define WINDOW_CLASS	_T("VTC2")
#define WINDOW_TITLE	WINDOW_CLASS
#define	WINDOW_STYLE	WS_OVERLAPPEDWINDOW
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720
#define AssertHR(expr) { HRESULT hr = expr; if (FAILED(hr)) throw 0; /*gcnew ComponentModel::Win32Exception(hr, #expr);*/}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
void Draw();

const UINT	FrameCount = 2;

Graphics* graphics;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpszCmdLine, int nCmdShow)
{
	// �E�B���h�E���쐬
	WNDCLASSEX	wndclass = {};

	// �E�B���h�E�N���X��o�^
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = WINDOW_CLASS;
	RegisterClassEx(&wndclass);

	RECT	windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

	AdjustWindowRect(&windowRect, WINDOW_STYLE, FALSE);

	// �E�B���h�E���쐬
	HWND	hWnd = CreateWindow(
		WINDOW_CLASS,
		WINDOW_TITLE,
		WINDOW_STYLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	graphics = new Graphics();
	if (!graphics->Init(hWnd)) {
		delete graphics;
		return -1;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	MSG	msg;

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete graphics;

	return (int)msg.wParam;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch (nMsg) {
	case WM_PAINT:
		// �`��
		Draw();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, nMsg, wParam, lParam);
	}

	return 0;
}
int count = 0;
void Draw()
{
	if (count > 60) {
		count = 0;
	}
	else {
		count++;
	}

	graphics->BeginDraw();
	//graphics->ClearScreen(0,0,1,0.1);
	graphics->DrawRectangle(0,0, WINDOW_WIDTH, WINDOW_HEIGHT, 0,0,0,0.02);

	if (count % 10 == 1) {
		int loopCount = rand() % 6;
		for (int i = 0; i < loopCount; i++)
		{
			graphics->DrawCircle(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, rand() % 100,
				(rand() % 100) / 100.0f,
				(rand() % 100) / 100.0f,
				(rand() % 100) / 100.0f,
				(rand() % 100) / 100.0f);
		}
	}

	graphics->EndDraw();
}