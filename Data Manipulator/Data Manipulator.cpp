// Data Manipulator.cpp : main project file.

#include "stdafx.h"
#include "Manipulator.h"
using namespace DataManipulator;
using namespace std;
[STAThreadAttribute]
int main(cli::array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Manipulator());
	return 0;
}
