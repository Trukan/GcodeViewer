#pragma once
using namespace System;
using namespace System::Collections;

public ref class GcodeData
{
public:
	System::Collections::Generic::List<String^>^ commands;
	System::Collections::IEnumerator^ enumerator;

	GcodeData();
	~GcodeData();
	property String^ GcodeData::str[int]{
		String^ get(int index);
	void set(int index, String^ value);
	}
	bool loadFile(String^ filepath);
};

