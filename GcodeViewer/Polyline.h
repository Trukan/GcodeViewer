#pragma once
#include "State.h"
//#include "Kadr.h"

namespace GData {

	using namespace System;
	using namespace System::Collections;
	//хранилище параметров команд одной строки
	//класс, предназначен для содержания координат точек ломаной неразрывной линии одного цвета (RGB)
	public ref class Polyline sealed {
	public:
		Polyline(int _n);
		//указывая начальную емкость массивов, инициализирует их
		Polyline(int _n,
			Collections::Generic::List<float>^ _x,
			Collections::Generic::List<float>^  _y,
			Collections::Generic::List<float>^  _z) :n(n), x(_x), y(_y), z(_z) {};
		~Polyline()				//деструктор
		{
			delete x;
			delete y;
			delete z;
		}
	public:
		GState gstate = GState::None;
		float feed;				//подача в мм/мин
		MState mstate = MState::None;
		int speedrate;			//скорость вращения
		int n;					//длина массивов
		Collections::Generic::List<float>^ x;		//массивы координат
		Collections::Generic::List<float>^ y;
		Collections::Generic::List<float>^ z;
		int red, green, blue;		//значения цвета в формате RGB 

		bool update();
	//	bool setLastPointAsFirst(Polyline^);

		//	static bool    operator ==(const Polyline^, const Polyline^);
		static Polyline^ operator /(Polyline^, float d);




	};

}