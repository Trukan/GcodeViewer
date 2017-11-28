#include "GLctrl.h"

using namespace System;

GLctrl::GLctrl()
{
}

System::Void GLctrl::timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		glctrl->Invalidate();
		Console::Write(" tick ");
	}
GLctrl::~GLctrl()
{
}
