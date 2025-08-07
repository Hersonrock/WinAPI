#include <Windows.h>
#include <string>


LRESULT CALLBACK WndProc(HWND  hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, LPSTR LpCmdLine, int nCmdShow) {

	MessageBox(NULL, "Goodbye, cruel world!", "Note", MB_OK);
	return 0;
}

