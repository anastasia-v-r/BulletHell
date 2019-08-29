#include <exception>
#include <iostream>

#include "Application.h"

int main() {
	try
	{
		Application app;
		app.runApp();
	}
	catch (std::exception &ex)
	{
		std::cout << "\nEXCEPTION: " << ex.what() << std::endl;
	}
}