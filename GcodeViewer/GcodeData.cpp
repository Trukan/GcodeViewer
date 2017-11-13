#include "GcodeData.h"

using namespace GData;
using namespace System;
using namespace System::Collections;
using namespace System::IO;

//конструктор Polyline, инициализирует массивы координат по соответствующей длине
GData::Polyline::Polyline(int _n)
{
	Polyline::x = gcnew array<float>(_n);
	Polyline::y = gcnew array<float>(_n);
	Polyline::z = gcnew array<float>(_n);
}

//оператор деления, делит координаты на конкретное число, 
//Возвращает измененный экземпляр переданого параметра
Polyline ^ GData::Polyline::operator/(Polyline ^ p, float d)
{
	for (size_t i = 0; i < p->n; i++)
	{
		p->x[i] = p->x[i] / d;
		p->y[i] = p->y[i] / d;
		p->z[i] = p->z[i] / d;
	}
	return p;
}

//конструктор, инициализирует коллекцию commands
GcodeData::GcodeData()
{
	commands = gcnew System::Collections::Generic::List<String^>(1);
}

GcodeData::~GcodeData()
{

}

//загрузка файла по filepath
bool GcodeData::loadFile(String^ filepath)
{
	if (filepath == nullptr)
		return false;
	try {
		commands->Clear();
		StreamReader ^sr = gcnew StreamReader(filepath);
		while (!sr->EndOfStream) {
			commands->Add(sr->ReadLine());
		}
		sr->Close();
		delete sr;
	}
	catch (System::OutOfMemoryException^ outME) {
		Console::WriteLine(outME->Message);
		return false;
	}
	catch (System::IO::IOException^ ioE) {
		Console::WriteLine(ioE->Message);
		return false;
	}
	return true;
}

System::Collections::Generic::List<Polyline^>^ GData::GcodeData::tranlate(System::Collections::Generic::List<String^>^ cmds)
{
	if (cmds == nullptr || cmds->Count < 1)
		return nullptr;
	System::Collections::Generic::List<Polyline^>^ lines;
	String^ str = cmds[0];


	return lines;
}


String^ GcodeData::str::get(int index) {
	if (index < commands->Count) {
		return commands[index];
	}
	else return nullptr;
}
void GcodeData::str::set(int index, String^ value) {
	commands[index] = value;
}


