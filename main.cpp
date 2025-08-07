#include <Windows.h>
#include <string>

HWND hwnd;
std::string className = "myWindowClass";

LRESULT CALLBACK WndProc(HWND  hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int initWindow(HINSTANCE hInstance, int nCmdShow);
int messageLoop(HINSTANCE hInstance, int nCmdShow);
int run(HINSTANCE hInstance, int nCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, LPSTR LpCmdLine, int nCmdShow) {

	int runValue = run(hInstance, nCmdShow);

	return runValue;

}

int run(HINSTANCE hInstance, int nCmdShow) {
	if (initWindow(hInstance, nCmdShow) != 0)
		return 1;
	int wParam = messageLoop(hInstance, nCmdShow);

	return 	wParam;
}

int messageLoop(HINSTANCE hInstance, int nCmdShow) {
	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

int initWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className.c_str();
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registering the window
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	// Creating the window
	hwnd = CreateWindow(
		className.c_str(),
		className.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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