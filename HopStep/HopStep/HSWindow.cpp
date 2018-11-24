#include "stdafx.h"
#include "HsWindow.h"

namespace HopStep
{
	std::wstring windowClassName = TEXT("HSBasicWindow");

	LRESULT CALLBACK HSBasicWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	void HSWindow::Create(HINSTANCE hInstance, int nCmdShow, std::wstring& name, int width, int height)
	{
		WNDCLASSEX wc;
		HWND hwnd;

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = HSBasicWindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = windowClassName.c_str();
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
			return;
		}

		hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,	windowClassName.c_str(), name.c_str(), WS_OVERLAPPEDWINDOW,	CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

		if (hwnd == NULL)
		{
			MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
			return;
		}

		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);
	}
}