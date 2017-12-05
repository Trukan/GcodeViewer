#include "Kadr.h"

using namespace GData;
using namespace System;
using namespace System::Collections;
using namespace System::Data;


Kadr::Kadr()
{
	this->reset(true);
}
void Kadr::reset(bool full) {
	if (full) {
		feedNoLoad = 2000;
		feedrate = 0;
		curGstate = GState::None;
		formatInfo = gcnew NumberFormatInfo();
		fool = true;
		s = 0;
	}
	bg = false;
	bm = false;
	bs = false;
	bx = false;
	by = false;
	bz = false;
	bi = false;
	bj = false;
	bk = false;
	bf = false;
}
//функция транслирует строчные команды в указанной строке,
// в ломаную линию polyline, возвращает успешно ли преобразование
bool Kadr::getPolyline(String^ str, Polyline^ %pl)
{
	//если строка пуста, то нечего и делать
	if (String::IsNullOrWhiteSpace(str)) {
		pl = gcnew Polyline(0);
		return true;
	}

	//подготовка, обнуление
	reset(false);
	Polyline^ tpl = gcnew Polyline(1);
	int paramInt = 0;
	int curindex = 0, tmpindex = 0;

	str = str->Trim();

	while (curindex < str->Length) {
		tmpindex = curindex;

		switch (str[curindex]) {
			//Подготовительные (основные) команды
		case 'G':
			if (!getInt(str, paramInt, tmpindex, curindex))
				return false;
			curGstate = safe_cast<GState>(paramInt);
			bg = true;
			Console::Write("G" + paramInt);
			break;
		case 'X':
			if (!getFloat(str, 'X', tmpindex, curindex))
				return false;
			break;
		case 'Y':
			if (!getFloat(str, 'Y', tmpindex, curindex))
				return false;
			break;
		case 'Z':
			if (!getFloat(str, 'Z', tmpindex, curindex))
				return false;
			break;
			//скорость рабочей подачи, для фрезерных милиметры в минуту, mm/min
		case 'F':
			if (!getFloat(str, 'F', tmpindex, curindex))
				return false;
			break;
			//частота вращения шпинделя
		case 'S':
			if (!getInt(str, paramInt, tmpindex, curindex))
				return false;
			bs = true;
			break;
			//case P:	//параметр команды
			//case R:	//не используется в этой версии, параметр стандартного цикла или радиус
			//case D:	//не используется в этой версии, параметр коррекции выбранного инструмента
			//case L:	//не используется в этой версии, число вызовов подпрограммы
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси X.
		case 'I':
			if (!getFloat(str, 'I', tmpindex, curindex))
				return false;
			break;
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси Y
		case 'J':
			if (!getFloat(str, 'J', tmpindex, curindex))
				return false;
			break;
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние дуги по оси Z.
		case 'K':
			if (!getFloat(str, 'K', tmpindex, curindex))
				return false;
			break;
			//Вспомогательные (технологические) команды
		case'M':
			if (!getInt(str, paramInt, tmpindex, curindex)) {
				return false;
			}
			m = safe_cast<MState>(paramInt);
			bm = true;
			Console::Write("M" + paramInt);
			break;
			//номер инструмента
		case 'T':
			if (!getInt(str, paramInt, tmpindex, curindex))
				return false;
			Console::Write("T" + paramInt);
			break;
		default:	//обработка нерегламентированных (ошибочных) значений
			Console::WriteLine("Wrong Symbol \"" + str + "\":" + str[curindex] + " from tmpindex:" + tmpindex + "curindex:" + curindex);
			return false;
		}
	}

	//заводим модульные и режимные состояния
	if (bg)tpl->gstate = curGstate;
	if (bm)tpl->mstate = m;
	if (bs)tpl->speedrate = s;
	if (bf)tpl->feed = feedrate;
	//если нет параметров-координат в строке
	if (!(bx || by || bz || bi || bj || bk)) {

	}
	else {
		//при вводе координат, шпиндель должен уже вращаться, если это не подача на холостом ходу
		//а текущий режим должен быть выбран, подача при нем должна иметь значение больше нуля
		//на холостом ходу может действовать подача по умолчанию
		if (m == MState::StartRotateClockwise || curGstate == GState::NotLoad) {
			if ((curGstate == GState::NotLoad || curGstate == GState::LineRun || curGstate == GState::CircClockwise)
				&& (curGstate == GState::NotLoad || feedrate > 0)) {
				//проверим, все ли параметры на месте для Kруговой интерполяции (только для движения по часовой стрелке)
				if (curGstate == GState::CircClockwise && ((bi&&bj&&bx&&by) || (bj&&bk&&by&&bz) || (bk&&bi&&bz&&bx))) {
					if (bi&&bj&&bx&&by) {

					}
					if (bj&&bk&&by&&bz) {

					}
					if (bk&&bi&&bz&&bx) {

					}
					tpl->stickToColor();
				}
				else {


					//проверим, все ли параметры на месте для Линейной интерполяции
					if ((curGstate == GState::NotLoad || curGstate == GState::LineRun) && !(bi || bj || bk)) {
						if (bx)tpl->x->Insert(0, Kadr::x);
						if (by)tpl->y->Insert(0, Kadr::y);
						if (bz)tpl->z->Insert(0, Kadr::z);
						if (curGstate == GState::NotLoad) {
							Polyline::setColor(tpl, 170, 170, 170);
						}
						else {
							tpl->stickToColor();
						}
					}
					else {
						if (curGstate == GState::CircClockwise) {
							Console::WriteLine(" Wrong coor for Gstate:CircleInterpol " + str + ";");
							return false;
						}
						if (curGstate == GState::NotLoad || curGstate == GState::LineRun) {
							Console::WriteLine(" Wrong coor for Gstate:notload or linerun " + str + ";");
							return false;
						}
					}
				}
			}
			else {
				Console::WriteLine(" need GState or Feedrate " + str + ":feedrate:" + feedrate + "\n");
				return false;
			}
		}
		else {
			Console::WriteLine(" Turn on M03 before " + str + ";");
			return false;
		}
		//здесь будет определение цвета линии по величине подачи, и скорости вращения
		//или не будет
	}

	return true;
}

//возвращает строку, содержащую первое число от символа заданной строки с заданным индексом,
//если такого числа нет, то возвращает System::String::Empty, если найдет две точки подряд то вернет nulptr
//в backlastindex передается индекс на котором остановился поиск числа
String ^ Kadr::getNumeric(String ^str, int startIndex, int &backlastindex)
{
	int start = startIndex, end = startIndex;
	bool wasdot = false;
	while (start < str->Length && Kadr::isGoodLetter(str[start]))
	{
		start++;
	}
	end = start;
	//если мы не перебрали до конца строки
	if (end < str->Length) {
		end++;
		//если наткнулись на точку, отметим это, что бы учесть дальше
		if (str[start] == '.') wasdot = true;
	}
	// (указатель end за пределами строки) И (символ по end не пробел) И 
	// И ( символ является цифрой ИЛИ ( (  символ является точкой ) ИСКЛЮЧАЮЩЕЕ_ИЛИ число в целом уже начиналось с точки) )
	//последняя проверка для определения двух точек в числе
	while (end < str->Length && (((str[end] == '.') && (!wasdot)) ^ Kadr::isGoodNumber(str[end]))) {
		//while (end < str->Length && !Char::IsWhiteSpace(str[end]) && !(str[end] == 'Y') && !(str[end] == 'Z')
		//	&& !(str[end] == 'F') && !(str[end] == 'S') && (((str[end] == '.') ^ wasdot) || Char::IsDigit(str[end]))) {
		if (str[end] == '.') wasdot = true;
		end++;
	}

	//нет ли двух точек подряд?
	if (end < str->Length && str[end] == '.') {
		Console::Write("parseFloat:nulptr:dot id:" + start + "-" + end + " str-substr: " + str + "-" + str->Substring(start, end - start));
		return nullptr;
	}
	backlastindex = end;
	return str->Substring(start, end - start);
}

//возващает true, если успешно извлечение ближайшего целого числа result из строки str,
//начиная с индекса startIndex,
//передает индекс на котором остановился поиск
bool Kadr::getInt(String ^str, int &result, int startIndex, int &backlastindex) {
	//достаем строку содержащую число
	String^ resultStr = Kadr::getNumeric(str, startIndex, backlastindex);
	//если строка пустая, не содержит символов, то есть, если начиная с конкретного символа нет чисел
	if (System::String::Empty->Equals(resultStr)) {
		Console::WriteLine("not get int \"" + str + "\"is empty. index " + startIndex);
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	//если вместо строки вернуло nulptr
	if (resultStr == nullptr) {
		Console::WriteLine(" Cannot get int (nulptr)\"" + str + "\" index " + startIndex + "too many dots");
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	//число началось позже startindex+1, значит, были прочитаны лишние комманды и не встретилось число,
	//то есть нехватает числа сразу после комманды по startIndex-1, это ошибочная строка
	if (backlastindex - startIndex - 1 > resultStr->Length) {
		Console::WriteLine(" int is not that whitch  expected\"" + str + "\"need int by index " + startIndex);
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	//проверки подстроки содержащей число пройдены, парсим
	if (!System::Int32::TryParse(resultStr, NumberStyles::Integer, formatInfo, result)) {
		Console::WriteLine("Falture to TryParse for int");
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	return true;
}

//возващает true, если успешно извлечение ближайшего числа с плавающей точкой
//указанного символьного параметра param из строки str, начиная с индекса startIndex,
//передает индекс на котором остановился поиск
bool Kadr::getFloat(String ^str, wchar_t param, int startIndex, int &backlastindex) {
	float result = 0;
	//достаем строку содержащую число
	String^ resultStr = Kadr::getNumeric(str, startIndex, backlastindex);
	//если строка пустая, не содержит символов, то есть, если начиная с конкретного символа нет чисел
	if (System::String::Empty->Equals(resultStr)) {
		Console::WriteLine("not get float \"" + str + "\"is empty. index " + startIndex);
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	//если вместо строки вернуло nulptr
	if (resultStr == nullptr) {
		Console::WriteLine(" Cannot get int (nulptr)\"" + str + "\" index " + startIndex + "too many dots");
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}

	//проверки подстроки содержащей число пройдены, парсим
	if (!System::Single::TryParse(resultStr, NumberStyles::AllowDecimalPoint | NumberStyles::AllowLeadingSign, formatInfo, result)) {
		Console::WriteLine("Falture to TryParse for float\"" + str + "\"-" + resultStr);
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	switch (param) {
	case 'X':
		x = result;
		bx = true;
		Console::Write("X" + x);
		break;
	case 'Y':
		y = result;
		by = true;
		Console::Write("Y" + y);
		break;
	case 'Z':
		z = result;
		bz = true;
		Console::Write("Z" + z);
		break;
		//параметр команды
//	case 'P':	
	case 'F':
		if (result > 0) {
			if (curGstate != GState::None)
				feedrate = result;
			bf = true;
			Console::Write("F" + feedrate);
			break;
		}
		else {
			Console::WriteLine("F.Error<=0");
			Kadr::reset(false);
			backlastindex = str->Length;
			return false;
		}
		//частота вращения шпинделя

		//case R:	//не используется в этой версии, параметр стандартного цикла или радиус
		//case D:	//не используется в этой версии, параметр коррекции выбранного инструмента
		//case L:	//не используется в этой версии, число вызовов подпрограммы
		//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси X.
	case 'I':
		i = result;
		bi = true;
		Console::Write("I" + i);
		break;
		//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси Y
	case 'J':
		j = result;
		bj = true;
		Console::Write("J" + j);
		break;
		//Параметр дуги при круговой интерполяции. Инкрементальное расстояние дуги по оси Z.
	case 'K':
		k = result;
		bk = true;
		Console::Write("K" + k);
		break;
	default:	//обработка нерегламентированных (ошибочных) значений
		Console::WriteLine(" wrong param for get result \"" + str + "\" param: " + param + ".");
		Kadr::reset(false);
		backlastindex = str->Length;
		return false;
	}
	return true;
}

bool GData::Kadr::isGoodLetter(wchar_t ch)
{	// :88-X;:89-Y;:90-Z;:73-I;:74-J;:75-K;:71-G;:77-M;:70-F;:83-S;:45--;:46-.;
	bool res = (
		(ch == 'X') ||
		(ch == 'Y') ||
		(ch == 'Z') ||
		(ch == 'I') ||	// (safe_cast<Int16>(ch) == 73) ||
		(ch == 'J') ||	// (safe_cast<Int16>(ch) == 74) ||
		(ch == 'K') ||	// (safe_cast<Int16>(ch) == 75) ||
		(ch == 'F') ||
		(ch == 'S') ||
		(ch == 'M') ||
		(ch == 'G') ||
		(ch == 'T'));
	//bool res = ((ch == 'Y') || Char::IsLetter(ch)) && !(ch == '.');
	return res;
}
bool Kadr::isGoodNumber(wchar_t ch) {
	bool res = ((safe_cast<Int16>(ch) >= 48) && (safe_cast<Int16>(ch) <= 57)) || (safe_cast<Int16>(ch) == 45);
	//bool res = ((ch == 'Y') || Char::IsLetter(ch)) && !(ch == '.');
	return res;
}

