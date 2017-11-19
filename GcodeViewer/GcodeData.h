#pragma once
#include "State.h"
#include "Polyline.h"
#include "Kadr.h"

namespace GData {
	using namespace System;
	using namespace System::Collections;
	using namespace System::Drawing;
	using namespace System::Globalization;
	//	using namespace OpenTK;
	//	using namespace OpenTK::Platform::Windows;
	//	using namespace OpenTK::Graphics::OpenGL;

	//класс данных, содержит коллекцию строк комманд, загружаемых из файла, 
	//или написаных в таблице программы, содержит коллекцию ломаных линий и их данные
	public ref class GcodeData
	{
	public:
		System::Collections::Generic::List<Int32>^ errorRows;
		System::Collections::Generic::List<String^>^ commands;
		System::Collections::Generic::List<Polyline^>^ polyline;

		GcodeData();
		~GcodeData();
		//свойство для обращения к коллекции строк комманд в духе gcoded->str[i]
		property String^ GcodeData::str[int]{
			String^ get(int index);
		void set(int index, String^ value);
		}

			//функция загрузки данных из файла в коллекцию строк комманд
		bool loadFile(String^ filepath);

		//функция транслирующая строчные команды коллекции в траекторию, 
		// в ломаные линии некоторых цветов в коллекцию polyline
		System::Collections::Generic::List<Polyline^>^ tranlate(System::Collections::Generic::List<String^>^ cmds);

	};

}