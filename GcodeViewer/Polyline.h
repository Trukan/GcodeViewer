#pragma once
#include "State.h"

namespace GData {

	//хранилище параметров команд одной строки
	//класс, предназначен для содержания координат точек ломаной неразрывной линии одного цвета (RGB)
	public ref class Polyline sealed {
	public:
		static GState gstate = GState::None;
		static MState mstate = MState::None;
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
		float red, green, blue;		//значения цвета в формате RGB 
									//	Color color;
	};

}