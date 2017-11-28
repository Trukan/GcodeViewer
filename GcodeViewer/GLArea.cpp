#include "GLArea.h"

using namespace GLArea;
using namespace GLAr;

GLArea::GLAr::GLAr(OpenTK::GLControl ^ glControl)
{
	glCtrl = glControl;
}

GLArea::GLAr::~GLAr()
{
}
//обработка прокрутки колеса мыши по компоненту Control1
System::Void gl_mouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Delta > 0)
			//от себя
		{
			GLAr::eyeX = GLAr::eyeX*GLAr::multiplyEye;
			GLAr::eyeY = GLAr::eyeY*GLAr::multiplyEye;
			GLAr::eyeZ = GLAr::eyeZ*GLAr::multiplyEye;

		}
		else
			// на себя
		{
			eyeX = eyeX / multiplyEye;
			eyeY = eyeY / multiplyEye;
			eyeZ = eyeZ / multiplyEye;
		}
		changeModelView();
	}
//обработка сигнала о загрузке компонента
System::Void gl_Load(System::Object^  sender, System::EventArgs^  e) {
	glLoaded = true;
	GL::ClearColor(Color::WhiteSmoke);
	GL::Enable(EnableCap::DepthTest);

	GL::MatrixMode(MatrixMode::Projection); //работаем с трехмерной проекцией
	GL::Ortho(-1, 1, -1, 1, -1, 1); //Указываем систему координат

									//Матрица отвечающая за фруструм
	Matrix4 perspective = Matrix4::CreatePerspectiveFieldOfView((float)(90 * Math::Asin(1.0f) / 90), (float)glCtrl->Width / glCtrl->Height, (float)0.05, (float)2000);
	GL::LoadMatrix(perspective);
	GL::ClearColor(Color::WhiteSmoke); //указываем цвет фона
									   //Здесь мы задаем нашу камеру в точке(30, 70, 80), 
									   //направление взгляда в центр системы координта(0, 0, 0).
									   //Ориентация такая, что ось OZ направлена вверх.
	changeModelView();
}
//обработка события перерисовки, происходит по необходимости, изменении размеров окна и прочее
System::Void gl_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	if (!glLoaded)
		return;
	GL::Clear(ClearBufferMask::ColorBufferBit | ClearBufferMask::DepthBufferBit);
	//рисуем обозначение системы координат
	GL::Color3(Color::Gray); //цвет, которым будем рисовать
	GL::Begin(PrimitiveType::Lines); //Что будем рисовать: линии
	GL::Vertex3(w, 0, 0); GL::Vertex3(w, w, 0);
	GL::Vertex3(w, w, 0); GL::Vertex3(0, w, 0);
	GL::Vertex3(w, w, 0); GL::Vertex3(w, w, w);
	GL::Vertex3(0, w, 0); GL::Vertex3(0, w, w);
	GL::Vertex3(0, w, w); GL::Vertex3(0, 0, w);
	GL::Vertex3(0, w, w); GL::Vertex3(w, w, w);
	GL::Vertex3(0, 0, w); GL::Vertex3(w, 0, w);
	GL::Vertex3(w, 0, w); GL::Vertex3(w, 0, 0);
	GL::Vertex3(w, 0, w); GL::Vertex3(w, w, w);
	GL::End();
	GL::LineWidth(2.0f);
	//OX
	GL::Color3(Color::Green); //цвет, которым будем рисовать
	GL::Begin(PrimitiveType::Lines); //Что будем рисовать: линии
	GL::Vertex3(0, 0, 0); GL::Vertex3(30, 0, 0);
	GL::End();
	//OY
	GL::Color3(Color::Blue);
	GL::Begin(PrimitiveType::Lines);
	GL::Vertex3(0, 0, 0); GL::Vertex3(0, 30, 0);
	GL::End();
	//OZ
	GL::Color3(Color::Red);
	GL::Begin(PrimitiveType::Lines);
	GL::Vertex3(0, 0, 0); GL::Vertex3(0, 0, 30);
	GL::End();
	glCtrl->SwapBuffers();
}

//обработка перемещения мыши по компоненту Control1
System::Void gl_mouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	mX = e->X;
	mY = e->Y;
	if (mdown) {

		angleG = ((double)(mX - mdX))*pi / (glCtrl->Width);
		angleV = ((double)(mY - mdY))*pi / (glCtrl->Height);
		rotateG(angleG);
		rotateV(angleV);
		//		eyeX = (float)(rXY*Math::Sin(Math::Asin(eyeX / rXY) + angleG));
		//			eyeY = (float)(rXY*Math::Cos(Math::Acos(eyeY / rXY) + angleG));
		changeModelView();
		mdX = mX;
		mdY = mY;
	}
}
//кнопка мыши нажата
System::Void gl_mouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (!mdown) {
		mdX = e->X;
		mdY = e->Y;
		//		angleG = Math::sin
	}
	mdown = true;
}
//кнопка мыши отжата
System::Void gl_mouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	mdown = false;

}
void GLArea::GLAr::changeModelView() {
	modelview = Matrix4::LookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);
	GL::MatrixMode(MatrixMode::Modelview);
	GL::LoadMatrix(modelview);
}
void  GLArea::GLAr::rotateG(double U) {
	rXY = Math::Sqrt((Math::Pow(eyeX, 2) + Math::Pow(eyeY, 2)));
	startAngG = startAngG + U;
	eyeX = (float)(rXY*Math::Sin(startAngG));
	eyeY = (float)(rXY*Math::Cos(startAngG));
}
void  GLArea::GLAr::rotateV(double U) {
	rXY = Math::Sqrt((Math::Pow(eyeX, 2) + Math::Pow(eyeY, 2)));
	rXYZ = Math::Sqrt((Math::Pow(eyeX, 2) + Math::Pow(eyeY, 2) + Math::Pow(eyeZ, 2)));
	startAngV = startAngV + U;
	eyeX = (float)(eyeX*rXYZ*Math::Cos(startAngV) / rXY);
	eyeY = (float)(eyeY*rXYZ*Math::Cos(startAngV) / rXY);
	eyeZ = (float)(rXYZ*Math::Sin(startAngV));

}

