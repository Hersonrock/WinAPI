#include "App.h"

App::App(HINSTANCE hInstance, int nCmdShow)
	: windowHandle_(nullptr),
	className_("myWindowClass"), 
	instanceHandle_(hInstance),
	initialWindowState_(nCmdShow)
{
	initWindow();
}

App::~App() {

	if (windowHandle_) {
		DestroyWindow(windowHandle_);
		windowHandle_ = nullptr;
	}
	UnregisterClass(className_.c_str(), instanceHandle_);
}

int App::run() {
	return 	messageLoop();
}

int App::messageLoop() {
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
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
	wcex.hInstance = this->instanceHandle_;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = this->className_.c_str();
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	// Registering the window
	try {
		if (!RegisterClassEx(&wcex))
			throw "Window Registration Failed!";
	}
	catch (const char* expression)
	{
		MessageBox(nullptr, expression, "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}


	// Creating the window
	windowHandle_ = CreateWindow(
		this->className_.c_str(),
		this->className_.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		nullptr,
		nullptr,
		this->instanceHandle_,
		nullptr
	);

	try
	{
		if (!windowHandle_)
			throw "Window Creation Failed!";
	}
	catch(const char* expression)
	{
		MessageBox(nullptr, expression, "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	ShowWindow(windowHandle_, this->initialWindowState_);
	UpdateWindow(windowHandle_);

	return 0;
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

	case WM_LBUTTONDOWN:
	{
		char FileNameC[MAX_PATH];
		HINSTANCE instanceHandle = GetModuleHandle(nullptr);
		GetModuleFileName(instanceHandle, FileNameC, MAX_PATH);
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