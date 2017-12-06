#pragma once
#include "Polyline.h"

namespace GData {
	using namespace System;
	using namespace System::Collections;
	using namespace System::Globalization;

	//хранилище параметров команд одной строки
	ref class Kadr
	{
	public:
		Kadr();

		//сброс, используется при инициализации и в случае ошибочных данных, если true, то полный сброс, сбросит все состояния
		static	void reset(bool full);

		//функция транслирует строчные команды в указанной строке,
		// в ломаную линию polyline, возвращает успешно ли преобразование
		static	bool getPolyline(String ^ str, Polyline^ %pl);


		static	float x, y, z, i, j, k;
		static float lx=0, ly=0, lz=0; //предыдущие значения координат, потребуется для круговой интероляции
		static	bool bg, bf,
			bm, bs,
			bx, by, bz,
			bi, bj, bk,
			fool;	//показывает, был ли полный сброс
		static	int s = 0;
		static GState curGstate;
		static	float feedrate;
		static	float feedNoLoad;
		static	MState m;
		static	NumberFormatInfo^ formatInfo;
		static	Polyline^ polyline;

	private:
		//возвращает строку, содержащую первое число от символа заданной строки с заданным индексом,
		//если такого числа нет, то возвращает System::String::Empty, если найдет две точки подряд то вернет nulptr
		static	String^ getNumeric(String^, int startIndex, int &backlastindex);

		//возващает true, если успешно извлечение ближайшего целого числа result из строки str,
		//начиная с индекса startIndex,
		//передает индекс на котором остановился поиск
		static	bool getInt(String ^str, int &result, int startIndex, int &backlastindex);

		//возващает true, если успешно извлечение ближайшего числа с плавающей точкой
		//указанного символьного параметра param из строки str, начиная с индекса startIndex,
		//передает индекс на котором остановился поиск
		static	bool getFloat(String ^str, wchar_t param, int startIndex, int &backlastindex);

		static	bool isGoodNumber(wchar_t ch);
		//интерполирует сектор круга в списки координат
		static	bool interpolate(float lx, float ly, float lz, float x, float y, float i, float j,
			Generic::List<float>^ listx, Generic::List<float>^ listy, Generic::List<float>^ listz);

		static	bool isGoodLetter(wchar_t);
	};
}
