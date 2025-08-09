#include <Windows.h>
#include "App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE PrevInstance, LPSTR LpCmdLine, int nCmdShow) {

	int statusReturn;

	try 
	{
		App app{ hInstance, nCmdShow };
		statusReturn = app.run();
	}
	catch (const std::system_error& e)
	{
		std::string error_str = std::format("Caught system_error with code {} meaning {}",
			                   e.code().value(),
			                   e.what());
		//std::string error_str = std::format("Caught system_error with code {}" , e.what());

		MessageBox(nullptr, error_str.c_str(), "Error!", MB_ICONEXCLAMATION | MB_OK);
		statusReturn = 1;
	}	
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Error!", MB_ICONEXCLAMATION | MB_OK);
		statusReturn = 1;
	}

	return statusReturn;

}

