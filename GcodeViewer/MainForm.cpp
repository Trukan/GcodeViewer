#include "MainForm.h"
#include "GcodeData.h"
using namespace System;
using namespace System::Windows::Forms;

cli::array<String^>^ GcodeViewer::MainForm::getText(String^ filePath)
{
	cli::array<String^>^ tesText;
	tesText = gcnew array<String^>(28) {
		"T1M6",
			"G17",
			"G0Z10.000",
			"G0X0.000Y0.000S18000M3",
			"G0X7.000Y50.000Z10.000",
			"G1Z - 3.000F1200.0",
			"G1Y170.000F2400.0",
			"G2X50.000Y213.000I43.000J0.000",
			"G1X170.000",
			"G2X213.000Y170.000I0.000J - 43.000",
			"G1Y50.000",
			"G2X170.000Y7.000I - 43.000J - 0.000",
			"G1X50.000Y7.000",
			"G2X7.000Y50.000I - 0.000J43.000",
			"G1Z - 6.000F1200.0",
			"G1Y170.000F2400.0",
			"G2X50.000Y213.000I43.000J0.000",
			"G1X170.000",
			"G2X213.000Y170.000I0.000J - 43.000",
			"G1Y50.000",
			"G2X170.000Y7.000I - 43.000J - 0.000",
			"G1X50.000Y7.000",
			"G2X7.000Y50.000I - 0.000J43.000",
			"G0Z10.000",
			"G0X0.000Y0.000",
			"G0Z10.000",
			"G0X0.000Y0.000",
			"M30"
	};
	return tesText;
}

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GcodeViewer::MainForm Form;
	Application::Run(%Form);
}


