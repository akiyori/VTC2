#include <windows.h>
#include <tchar.h>

#include "graphics.h"
#include "game_controller.h"
#include "Level1.h"
#include "input.h"
#include "spdlog/spdlog.h"

#define WINDOW_CLASS	_T("VTC2")
#define WINDOW_TITLE	WINDOW_CLASS
#define	WINDOW_STYLE	WS_OVERLAPPEDWINDOW
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720
#define AssertHR(expr) { HRESULT hr = expr; if (FAILED(hr)) throw 0; /*gcnew ComponentModel::Win32Exception(hr, #expr);*/}

// ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
void Draw();

Graphics* graphics;
GameController* gameController;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR *lpszCmdLine, int nCmdShow)
{
	// ウィンドウを作成
	WNDCLASSEX	wndclass = {};

	// ウィンドウクラスを登録
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = WINDOW_CLASS;
	RegisterClassEx(&wndclass);

	RECT	windowRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

	AdjustWindowRect(&windowRect, WINDOW_STYLE, FALSE);

	// ウィンドウを作成
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

	// 描画クラス初期化
	graphics = new Graphics();
	if (!graphics->Init(hWnd)) {
		delete graphics;
		return -1;
	}

	// Logger初期化
	spdlog::set_pattern("[%H:%M:%S] %v");
	spdlog::set_async_mode(4096);
	auto asyncLogger = spdlog::basic_logger_st("async_file_logger", "logs/async_log.txt");

	// ゲーム初期化
	GameLevel::Init(graphics);
	GameController::Init();
	GameController::LoadInitialLevel(new Level1());

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// メッセージループ
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

// ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch (nMsg) {
	case WM_PAINT:
		// 描画
		Draw();
		break;
	case WM_LBUTTONUP:
		Input::clickPoint = Point(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_CHAR:
		Input::inputKey = (TCHAR)wParam;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		spdlog::drop_all();
		break;
	default:
		return DefWindowProc(hWnd, nMsg, wParam, lParam);
	}

	return 0;
}

void Draw()
{
	GameController::Update();

	graphics->BeginDraw();
	graphics->ClearScreen(0, 0, 0, 1);

	GameController::Render();

	graphics->EndDraw();
}