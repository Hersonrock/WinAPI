#include <Windows.h>
#include "App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, LPSTR LpCmdLine, int nCmdShow) {

	App app{hInstance, nCmdShow};
	return app.run();

}

