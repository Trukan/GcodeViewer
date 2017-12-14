#pragma once
#include "State.h"
//#include "Kadr.h"

namespace GData {

	using namespace System;
	using namespace System::Collections;
	//хранилище параметров команд одной строки
	//класс, предназначен дл€ содержани€ координат точек ломаной неразрывной линии одного цвета (RGB)
	//планируетс€ содержать в экземпл€рах этого класса круговые интерпол€ции или одиночные точки концов линий
	public ref class Polyline sealed {
	public:
		Polyline(int _n);		//указываетс€ начальна€ емкость массивов
		Polyline(int _n, Generic::List<float>^ _x, Generic::List<float>^  _y, Generic::List<float>^  _z)
			:n(n), x(_x), y(_y), z(_z) {};
		~Polyline() {};
	public:
		//рекомендуема€ предельна€ толщина снимаемого сло€, мм/об (без учета многозаходного инструмента)
		static float stickLimit = 0.5; 
		//рекомендуема€ предельна€ подача, мм 
		static float feedLimit = 4000;
		GState gstate = GState::None;
		float feed;				//подача в мм/мин
		MState mstate = MState::None;
		int speedrate;			//скорость вращени€
		int n;					//длина массивов
		Collections::Generic::List<float>^ x;		//массивы координат
		Collections::Generic::List<float>^ y;
		Collections::Generic::List<float>^ z;
		int red, green, blue;		//значени€ цвета в формате RGB 

		bool update();
		//	bool setLastPointAsFirst(Polyline^);

		//вычисл€ет толщину снимаемого за оборот шпиндел€ сло€, отражает валидность подачи в цвете,
		//в виде чисел red, green, blue
		void stickToColor();
		static Polyline^ operator /(Polyline^, float d);
		static void setColor(Polyline^p, int r, int g, int b);

	};

}