#pragma once
ref class GLctrl
{
public:
	GLctrl();
	System::Void timer1_Tick(System::Object ^ sender, System::EventArgs ^ e);
	OpenTK::GLControl ^glctrl;
	~GLctrl();
};

