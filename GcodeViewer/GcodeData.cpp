#include "GcodeData.h"

using namespace GData;
using namespace System;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::IO;

//конструктор Polyline, инициализирует массивы координат по соответствующей длине
GData::Polyline::Polyline(int _n)
{
	Polyline::x = gcnew array<float>(_n);
	Polyline::y = gcnew array<float>(_n);
	Polyline::z = gcnew array<float>(_n);
}

//оператор деления, делит координаты на конкретное число, 
//Возвращает измененный экземпляр переданого параметра
Polyline ^ GData::Polyline::operator/(Polyline ^ p, float d)
{
	for (int i = 0; i < p->n; i++)
	{
		p->x[i] = p->x[i] / d;
		p->y[i] = p->y[i] / d;
		p->z[i] = p->z[i] / d;
	}
	return p;
}

//конструктор, инициализирует коллекцию commands
GcodeData::GcodeData()
{
	commands = gcnew System::Collections::Generic::List<String^>(1);
	commands->Clear();
	errorRows = gcnew System::Collections::Generic::List<Int32>(1);
	errorRows->Clear();
	formatInfo = gcnew NumberFormatInfo();
}

GcodeData::~GcodeData()
{

}

//возвращает строку, содержащую первое число от символа заданной строки с заданным индексом,
//если такого числа нет, то возвращает System::String::Empty, если найдет две точки подряд то вернет nulptr
//в backlastindex передается индекс на котором остановился поиск числа
String ^ GData::GcodeData::getNumeric(String ^str, int startIndex, int &backlastindex)
{
	int start = startIndex, end = startIndex;
	bool isdot = false;
	while (start < str->Length &&((str[end] == 'Y')|| Char::IsLetter(str[start]) )&& !(str[start] == '.'))
	{
		start++;
		end++;
	}
	//если мы не перебрали до конца строки
	if (end < str->Length) {
		end++;
		//если наткнулись на точку, отметим это, что бы учесть дальше
		if (str[start] == '.') isdot = true;
	}
	// (указатель end за пределами строки) И (символ по end не пробел) И 
	// И ( символ является цифрой ИЛИ ( (  символ является точкой ) ИСКЛЮЧАЮЩЕЕ_ИЛИ число в целом уже начиналось с точки) )
	//последняя проверка для определения двух точек в числе
	while (end < str->Length && !Char::IsWhiteSpace(str[end]) && !(str[end] == 'Y') &&!(str[end] == 'Z') 
		&& !(str[end] == 'F') && !(str[end] == 'S') && (((str[end] == '.') ^ isdot) || Char::IsDigit(str[end]))) {
		if (str[end] == '.') isdot = true;
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
bool GData::GcodeData::getInt(String ^str, int &result, int startIndex, int &backlastindex) {
	//достаем строку содержащую число
	String^ resultStr = getNumeric(str, startIndex, backlastindex);
	//если строка пустая, не содержит символов, то есть, если начиная с конкретного символа нет чисел
	if (System::String::Empty->Equals(resultStr)) {
		Console::WriteLine("not get int \"" + str + "\"is empty. index " + startIndex);
		return false;
	}
	//если вместо строки вернуло nulptr
	if (resultStr == nullptr) {
		Console::WriteLine(" Cannot get int (nulptr)\"" + str + "\" index " + startIndex + "too many dots");
		return false;
	}
	//число началось позже startindex+1, значит, были прочитаны лишние комманды и не встретилось число,
	//то есть нехватает числа сразу после комманды по startIndex-1, это ошибочная строка
	if (backlastindex - startIndex - 1 > resultStr->Length) {
		Console::WriteLine(" int is not that whitch  expected\"" + str + "\"need int by index " + startIndex);
		return false;
	}
	//проверки подстроки содержащей число пройдены, парсим
	if (!System::Int32::TryParse(resultStr, NumberStyles::Integer, formatInfo, result)) {
		Console::WriteLine("Falture to TryParse for int");
		return false;
	}
	return true;
}

//возващает true, если успешно извлечение ближайшего целого числа с плавающей точкой result
//из строки str, начиная с индекса startIndex,
//передает индекс на котором остановился поиск
bool GData::GcodeData::getFloat(String ^str, float &result, int startIndex, int &backlastindex) {
	//достаем строку содержащую число
	String^ resultStr = getNumeric(str, startIndex, backlastindex);
	//если строка пустая, не содержит символов, то есть, если начиная с конкретного символа нет чисел
	if (System::String::Empty->Equals(resultStr)) {
		Console::WriteLine("not get float \"" + str + "\"is empty. index " + startIndex);
		return false;
	}
	//если вместо строки вернуло nulptr
	if (resultStr == nullptr) {
		Console::WriteLine(" Cannot get int (nulptr)\"" + str + "\" index " + startIndex + "too many dots");
		return false;
	}

	//проверки подстроки содержащей число пройдены, парсим
	if (!System::Single::TryParse(resultStr, NumberStyles::AllowDecimalPoint|NumberStyles::AllowLeadingSign, formatInfo, result)) {
		Console::WriteLine("Falture to TryParse for float\"" + str + "\"-"+resultStr);
		return false;
	}
	return true;
}
//загрузка файла по filepath
bool GcodeData::loadFile(String^ filepath)
{
	if (filepath == nullptr&&File::Exists(filepath))
		return false;
	try {
		commands->Clear();
		StreamReader ^sr = gcnew StreamReader(filepath);
		while (!sr->EndOfStream) {
			commands->Add(sr->ReadLine());
		}
		sr->Close();
		delete sr;
		tranlate(commands);
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

//функция транслирующая строчные команды коллекции в траекторию, 
// в ломаные линии некоторых цветов в коллекцию polyline
Generic::List<Polyline^>^ GData::GcodeData::tranlate(System::Collections::Generic::List<String^>^ cmds)
{
	//если коллекция пуста, то нечего и dелать
	if (cmds == nullptr || cmds->Count < 1)
		return nullptr;
	//модальные состояния (сквозные)
	GData::GState gstate = GState::None;
	GData::Modal mstate = Modal::None;
	//состояние строки
	GData::kadr^ kstate = gcnew kadr();
	System::Collections::Generic::List<Polyline^>^ lines;
	int i = 0;
	bool errR;
	float paramFloat;
	int paramInt;
	int curindex, tmpindex;
	//пройдемся по коллекции comds
	while (i < cmds->Count) {

		String^ str = gcnew String(cmds[i]);
		str = str->Trim();
		//если строка пустая, то следующая строка
		if (String::IsNullOrWhiteSpace(str)) {
			i++;
			continue;
		}
		//подготовка перед проходом по строке
		curindex = 0;
		errR = false;
		kstate->reset();

		while (curindex < str->Length) {

			paramInt = -1;
			paramFloat = safe_cast<float>(-0.0001);

			tmpindex = curindex;

			switch (str[curindex]) {
				//Подготовительные (основные) команды
			case 'G':
				if (!getInt(str, paramInt, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				gstate = safe_cast<GState>(paramInt);
				Console::Write("G");
				break;
			case 'X':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->x = paramFloat;
				kstate->bx = true;
				Console::Write("X" + paramFloat);
				break;
			case 'Y':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->y = paramFloat;
				kstate->by = true;
				Console::Write("Y");
				break;
			case 'Z':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->z = paramFloat;
				kstate->bz = true;
				Console::Write("Z");
				break;
				//параметр команды
			case 'P':
				if (!getInt(str, paramInt, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				Console::Write("P");
				break;
				//скорость рабочей подачи, для фрезерных милиметры в минуту, mm/min
			case 'F':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->f = paramFloat;
				kstate->bf = true;
				Console::Write("F");
				break;
				//частота вращения шпинделя
			case 'S':
				if (!getInt(str, paramInt, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->s = paramInt;
				kstate->bs = true;
				Console::Write("S");
				break;
				//case R:	//не используется в этой версии, параметр стандартного цикла или радиус
				//case D:	//не используется в этой версии, параметр коррекции выбранного инструмента
				//case L:	//не используется в этой версии, число вызовов подпрограммы
				//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси X.
			case 'I':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->i = paramFloat;
				kstate->bi = true;
				Console::Write("I");
				break;
				//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси Y
			case 'J':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->j = paramFloat;
				kstate->bj = true;
				Console::Write("J");
				break;
				//Параметр дуги при круговой интерполяции. Инкрементальное расстояние дуги по оси Z.
			case 'K':
				if (!getFloat(str, paramFloat, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				kstate->k = paramFloat;
				kstate->bk = true;
				Console::Write("K");
				break;
				//Вспомогательные (технологические) команды
			case 'M':
				if (!getInt(str, paramInt, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				mstate = safe_cast<Modal>(paramInt);
				Console::Write("M");
				break;
				//номер инструмента
			case 'T':
				if (!getInt(str, paramInt, tmpindex, curindex)) {
					errorRows->Add(i);
					errR = true;
					curindex = str->Length;
					continue;
				}
				Console::Write("T");
				break;
			default:	//обработка нерегламентированных (ошибочных) значений
				Console::WriteLine("Wrong content in this \"" + str + "\" from index " + tmpindex);
				errorRows->Add(i);
				errR = true;
				curindex = str->Length;
				continue;
			}
		}
		if (kstate->bf&&kstate->bs) {

			if (kstate->bx) {
			}
			if (kstate->by) {
			}
			if (kstate->bz) {

			}
			if (kstate->bz) {

			}
			if (kstate->bz) {

			}
			if (kstate->bz) {
			}
		}
		i++;
	}

	return lines;
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


