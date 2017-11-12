#include "GcodeData.h"

using namespace System;
using namespace System::Collections;
using namespace System::IO;
GcodeData::GcodeData()
{
	commands = gcnew System::Collections::Generic::List<String^>(2);
	enumerator = commands->GetEnumerator();
}

GcodeData::~GcodeData()
{
	throw gcnew System::NotImplementedException();
}

bool GcodeData::loadFile(String^ filepath)
{
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

String^ GcodeData::str::get(int index) {
	if (index < commands->Count) {
		return commands[index];
	}
	else return nullptr;
}
void GcodeData::str::set(int index, String^ value) {
	commands[index] = value;
}



