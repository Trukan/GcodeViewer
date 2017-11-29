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
		Polyline(int _n);		//указывается начальная емкость массивов
		Polyline(int _n, Generic::List<float>^ _x, Generic::List<float>^  _y, Generic::List<float>^  _z)
			:n(n), x(_x), y(_y), z(_z) {};
		~Polyline() {};
	public:
		//рекомендуемая предельная толщина снимаемого слоя, мм/об (без учета многозаходного инструмента)
		static float stickLimit = 0.1; 
		//рекомендуемая предельная подача, мм 
		static float feedLimit = 4000;
		GState gstate = GState::None;
		float feed;				//подача в мм/мин
		MState mstate = MState::None;
		int speedrate;			//скорость вращения
		int n;					//длина массивов
		Collections::Generic::List<float>^ x;		//массивы координат
		Collections::Generic::List<float>^ y;
		Collections::Generic::List<float>^ z;
	private:int red, green, blue;		//значения цвета в формате RGB 
	public:
		bool update();
		//	bool setLastPointAsFirst(Polyline^);

		//вычисляет толщину снимаемого за оборот шпинделя слоя, отражает валидность подачи в цвете,
		//в виде чисел red, green, blue
		void stickToColor();
		static Polyline^ operator /(Polyline^, float d);
		static void setColor(Polyline^p, int r, int g, int b);

	};

}