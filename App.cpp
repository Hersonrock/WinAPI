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
	int result;
	while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (result == 0)
	{
		return static_cast<int>(msg.wParam);
	}
	else
	{
		DWORD ec = GetLastError();
		throw std::system_error(static_cast<int>(ec), std::system_category());
	}

}

int App::initWindow() {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = this->instanceHandle_;
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wcex.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
	wcex.lpszClassName = this->className_.c_str();
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	// Registering the window
	if (!RegisterClassEx(&wcex)) {
		DWORD ec = GetLastError();
		throw std::system_error(static_cast<int>(ec), std::system_category());
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


	if (!windowHandle_) {
		DWORD ec = GetLastError();
		throw std::system_error(static_cast<int>(ec), std::system_category());

	}

	ShowWindow(windowHandle_, this->initialWindowState_);
	UpdateWindow(windowHandle_);

	return 0;
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {

	case WM_CREATE:
	{
		HMENU menuHandler, subMenuHandler;
		HICON iconHandler, iconSmallHandler;

		menuHandler = CreateMenu();

		subMenuHandler = CreatePopupMenu();
		AppendMenu(subMenuHandler, MF_STRING, ID_FILE_EXIT, "E&xit");
		AppendMenu(menuHandler, MF_STRING | MF_POPUP, (UINT)subMenuHandler, "&File");

		subMenuHandler = CreatePopupMenu();
		AppendMenu(subMenuHandler, MF_STRING, ID_STUFF_GO, "&Go");
		AppendMenu(subMenuHandler, MF_STRING, ID_STUFF_GOSOMEWHEREELSE, "&GoSmw");
		AppendMenu(menuHandler, MF_STRING | MF_POPUP, (UINT)subMenuHandler, "&Stuff");

		SetMenu(hwnd, menuHandler);


		iconHandler = reinterpret_cast<HICON>(LoadImage(NULL, "Icon1.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
		if (iconHandler)
			SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)iconHandler);
		else
			MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);


		iconSmallHandler = reinterpret_cast<HICON>(LoadImage(NULL, "Icon2.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
		if (iconSmallHandler)
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)iconSmallHandler);
		else
			MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);

	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case ID_STUFF_GO:
			MessageBox(hwnd, "You clicked Go!", "Woo!", MB_OK);
			break;
		}
		break;
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