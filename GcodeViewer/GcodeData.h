#pragma once
namespace GData {
	using namespace System;
	using namespace System::Collections;
	using namespace System::Drawing;
	using namespace System::Globalization;
	//	using namespace OpenTK;
	//	using namespace OpenTK::Platform::Windows;
	//	using namespace OpenTK::Graphics::OpenGL;

		//перечислени€ состо€ний по основным и техническим модальным командам дл€ проверки на последовательность
		//и логику комманд
	public enum class GState {
		None = -1, NotLoad = 0, LineRun = 1, CircClockwise = 2, CircCntrClockwise = 3, NewNullCoor = 10,
		SurfaceXY = 17, SurfaceZX = 18, SurfaceYZ = 19
	};
	public enum class Modal {
		None = -1, PreStart = 0, StopNoReset = 2, StartRotateClockwise = 3, StartRotateCntrClockwise = 4,
		StopRotate = 5, ChangeInsrtument = 6, StopWithReset = 30
	};
	//хранилище параметров команд одной строки
	public ref struct kadr
	{
		kadr() {};
		float x, y, z, i, j, k,f;
		bool bx, by, bz, bi, bj, bk, bf, bs;
		int s;
		//notful reset exclude f,s
		void reset() {
			bx = false;
			by = false;
			bz = false;
			bi = false;
			bj = false;
			bk = false;
		}
	};
	//класс, предназначен дл€ содержани€ координат точек ломаной неразрывной линии одного цвета (RGB)
	public ref class Polyline sealed {
	public:
		Polyline(int _n);
		Polyline(int _n, array<float>^ _x, array<float>^  _y, array<float>^  _z) :n(n), x(_x), y(_y), z(_z) {};
		~Polyline()				//деструктор
		{
			delete x;
			delete y;
			delete z;
		}
		//	static bool    operator ==(const Polyline^, const Polyline^);
		static Polyline^ operator /(Polyline^, float d);
		int n;					//длина массивов
		array<float>^ x;		//массивы координат
		array<float>^ y;
		array<float>^ z;
		float red, green, blue;		//значени€ цвета в формате RGB 
	//	Color color;
	};

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
		//свойство дл€ обращени€ к коллекции строк комманд в духе gcoded->str[i]
		property String^ GcodeData::str[int]{
			String^ get(int index);
		void set(int index, String^ value);
		}

			//функци€ загрузки данных из файла в коллекцию строк комманд
		bool loadFile(String^ filepath);

		//функци€ транслирующа€ строчные команды коллекции в траекторию, 
		// в ломаные линии некоторых цветов в коллекцию polyline
		System::Collections::Generic::List<Polyline^>^ tranlate(System::Collections::Generic::List<String^>^ cmds);

	private:
		NumberFormatInfo^ formatInfo;

		//возвращает строку, содержащую первое число от символа заданной строки с заданным индексом,
		//если такого числа нет, то возвращает System::String::Empty, если найдет две точки подр€д то вернет nulptr
		String^ getNumeric(String^, int startIndex, int &backlastindex);

		//возващает true, если успешно извлечение ближайшего целого числа result из строки str,
		//начина€ с индекса startIndex,
		//передает индекс на котором остановилс€ поиск
		bool GData::GcodeData::getInt(String ^str, int &result, int startIndex, int &backlastindex);

		//возващает true, если успешно извлечение ближайшего целого числа с плавающей точкой result
		//из строки str, начина€ с индекса startIndex,
		//передает индекс на котором остановилс€ поиск
		bool GData::GcodeData::getFloat(String ^str, float &result, int startIndex, int &backlastindex);
	};

}