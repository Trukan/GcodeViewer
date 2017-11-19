#include "MainForm.h"
#include "GcodeData.h"
using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GcodeViewer::MainForm Form;
	Application::Run(%Form);
}


