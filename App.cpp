#include "App.h"

App::App(HINSTANCE hInstance, int nCmdShow)
	: hWnd_(nullptr),
	className_("myWindowClass"), 
	hInstance_(hInstance),
	nCmdShow_(nCmdShow)
{

}

App::~App() {

}

int App::run() {
	if (initWindow() != 0)
		return 1;
	int wParam = messageLoop();

	return 	wParam;
}

int App::messageLoop() {
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

int App::initWindow() {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->hInstance_;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className_.c_str();
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registering the window
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	// Creating the window
	hWnd_ = CreateWindow(
		className_.c_str(),
		className_.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		this->hInstance_,
		NULL
	);

	if (!hWnd_) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	ShowWindow(hWnd_, this->nCmdShow_);
	UpdateWindow(hWnd_);

	return 0;
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

	case WM_LBUTTONDOWN:
	{
		char FileNameC[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(NULL);
		GetModuleFileName(hInstance, FileNameC, MAX_PATH);
		MessageBox(hwnd, FileNameC, "This program is:", MB_OK | MB_ICONINFORMATION);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return  DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}