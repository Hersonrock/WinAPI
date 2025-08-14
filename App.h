#pragma once
#include <Windows.h>
#include <string>
#include <stdexcept>
#include <system_error>
#include <format>
#include "resource.h"

class App {

public:

	App(HINSTANCE hInstance, int nCmdShow);
	~App();
	HWND windowHandle_;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	int run();

private:
	const std::string className_;
	HINSTANCE instanceHandle_;
	INT initialWindowState_;

	int initWindow();
	int messageLoop();
};