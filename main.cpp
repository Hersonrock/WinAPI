#include <Windows.h>
#include <string>


LRESULT CALLBACK WndProc(HWND  hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, LPSTR LpCmdLine, int nCmdShow) {

	
	return 0;
}

LRESULT CALLBACK WndProc(HWND  hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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