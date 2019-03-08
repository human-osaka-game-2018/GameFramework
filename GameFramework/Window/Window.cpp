//----------------------------------------------------------
// <filename>Window.cpp</filename>
//----------------------------------------------------------

#include "Window.h"

#include <Windows.h>
#include <tchar.h>

#include "RectSize.h"
#include "WindowParam/WindowParam.h"

namespace BaseFramework
{
	void Window::Create(const TCHAR* pAppName, const WNDPROC pWndProc)
	{
		RegisterWindowClass(pAppName, pWndProc);

		HINSTANCE hInstance = nullptr;
		WindowParam::GetInstanceHandle(&hInstance);

		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		RectSize windowSize;
		WindowParam::GetWindowSize(&windowSize);

		hWnd = CreateWindow(
			pAppName, pAppName,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT,
			static_cast<int>(windowSize.m_width), static_cast<int>(windowSize.m_height),
			NULL, NULL,
			hInstance,
			NULL);

		ResizeWindow();

		return;
	}

	void Window::RegisterWindowClass(const TCHAR* pAppName, const WNDPROC pWndProc)
	{
		WNDCLASSEX wndclass;
		wndclass.lpfnWndProc = (pWndProc) ? pWndProc : DefaultWndProc;

		//ウィンドウの名前
		wndclass.lpszClassName = pAppName;

		HINSTANCE hInstance = nullptr;
		WindowParam::GetInstanceHandle(&hInstance);
		wndclass.hInstance = hInstance;

		wndclass.style = CS_HREDRAW | CS_VREDRAW;

		//ウィンドウの背景の色
		wndclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));

		wndclass.hIcon = wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

		wndclass.lpszMenuName = nullptr;
		wndclass.cbSize = sizeof(wndclass);
		wndclass.cbClsExtra = wndclass.cbWndExtra = 0;

		RegisterClassEx(&wndclass);
	}

	void Window::ResizeWindow() const
	{
		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		//クライアント領域の取得
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		RectSize clientSize(clientRect);

		//ウィンドウ領域の取得
		RECT windowRect;
		GetWindowRect(hWnd, &windowRect);
		RectSize windowSize(windowRect);

		//フレームのサイズを計算
		RectSize frameSize(windowSize - clientSize);

		//想定しているクライアントのサイズを取得
		RectSize intendedClientSize;
		WindowParam::GetWindowSize(&intendedClientSize);

		//想定しているウィンドウサイズの計算
		RectSize intendedWindowSize(intendedClientSize + frameSize);

		//ウィンドウのサイズををフレーム分増加させる
		SetWindowPos(
			hWnd,
			NULL,
			CW_USEDEFAULT, CW_USEDEFAULT,
			static_cast<int>(intendedWindowSize.m_width), static_cast<int>(intendedWindowSize.m_height),
			SWP_NOMOVE);

		//ウィンドウを描画させる
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}

	LRESULT CALLBACK Window::DefaultWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (iMsg)
		{
			//ウィンドウの終了ボタンが押された時
		case WM_DESTROY:

			// プログラムの終了メッセージを投げる
			PostQuitMessage(0);

			break;

			//Alt + 特殊キーの処理に使う
		case WM_SYSKEYDOWN:

			if (wParam == VK_BACK)
			{
				//プログラムの終了メッセージを投げる
				PostQuitMessage(0);
			}

			break;
		}

		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
}
