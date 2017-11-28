#include "GcodeData.h"


using namespace GData;
using namespace System;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::IO;



//конструктор, инициализирует коллекцию commands
GcodeData::GcodeData()
{
	commands = gcnew System::Collections::Generic::List<String^>(1);
	commands->Clear();
	errorRows = gcnew System::Collections::Generic::List<Int32>(1);
	errorRows->Clear();
}

GcodeData::~GcodeData()
{

}

//загрузка файла по filepath
bool GcodeData::loadFile(String^ filepath)
{
	if (filepath == nullptr||!File::Exists(filepath))
		return false;
	Kadr::reset(true);
	try {
		commands->Clear();
		StreamReader ^sr = gcnew StreamReader(filepath);
		while (!sr->EndOfStream) {
			commands->Add(sr->ReadLine());
		}
		sr->Close();
		delete sr;
		tranlate(commands);
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

//функция транслирующая строчные команды коллекции в траекторию, 
// в ломаные линии некоторых цветов в коллекцию polylines
Generic::List<Polyline^>^ GData::GcodeData::tranlate(System::Collections::Generic::List<String^>^ cmds)
{
	//если коллекция пуста, то нечего и dелать
	if (cmds == nullptr || cmds->Count < 1)
		return nullptr;
	//модальные состояния (сквозные)
//	GData::GState gstate = GState::None;
//	GData::MState mstate = MState::None;
	//состояние строки
	GData::Kadr^ kstate = gcnew Kadr();
	System::Collections::Generic::List<Polyline^>^ lines;
	//пройдемся по коллекции comds
	int i = 0;
	while (i < cmds->Count) {

		String^ str = gcnew String(cmds[i]);
		Polyline^ line = gcnew Polyline(0);
		if (!Kadr::getPolyline(str, line)){
			errorRows->Add(i);
		}
		i++;
	}

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


