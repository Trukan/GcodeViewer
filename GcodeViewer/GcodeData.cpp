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
}

GcodeData::~GcodeData()
{

}

//возвращает строку, содержащую первое число от символа заданной строки с заданным индексом,
//если такого числа нет, то возвращает System::String::Empty, если найдет две точки подряд то вернет nulptr
//в backlastindex передается индекс на котором остановился поиск числа
String ^ GData::GcodeData::getFloat(String ^str, int startIndex, int &backlastindex)
{
	int start = startIndex, end = startIndex;
	bool isdot = false;
	while (start < str->Length && Char::IsLetter(str[start]) && !(str[start] == '.'))
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
	while (end < str->Length && !Char::IsWhiteSpace(str[end]) && !(str[end] == 'Y')&& (((str[end] == '.') ^ isdot) || Char::IsNumber(str[end]))) {
		if (str[end] == '.') isdot = true;
		end++;
	}
	//нет ли двух точек подряд?
	if (end < str->Length && str[end] == '.') {
		Console::Write("parseFloat:nulptr:dot id:" + start + "-" + end + " str-substr: " +str+ "-" + str->Substring(start, end - start));
		return nullptr;
	}
	Console::Write(" id:" + start + "-" + end + " ");
	backlastindex = end;
	return str->Substring(start, end - start);
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
System::Collections::Generic::List<Polyline^>^ GData::GcodeData::tranlate(System::Collections::Generic::List<String^>^ cmds)
{
	//если коллекция пуста, то нечего и елать
	if (cmds == nullptr || cmds->Count < 1)
		return nullptr;
	//начальные состояния
	GData::GState gstate = GState::None;
	GData::Modal modalstate = Modal::None;
	NumberFormatInfo^ formatInfo = gcnew NumberFormatInfo();
	formatInfo;
	System::Collections::Generic::List<Polyline^>^ lines;
	int i = 0;
	float numParam;
	int curindex, tmpindex;
	//пройдемся по коллекции comds
	while (i < cmds->Count) {

		String^ str = gcnew String(cmds[i]);
		str = str->Trim();
		if (String::IsNullOrWhiteSpace(str)) {
			i++;
			continue;
		}
		curindex = 0;
		numParam = -1;
		Console::WriteLine("");
		//while for curindex
		tmpindex = curindex;
//		wchar_t tmpchar = safe_cast<wchar_t>(str[curindex]);
		switch (str[curindex]) {
			//Подготовительные (основные) команды
		case 'G':
			Console::Write("G");
			break;
		case 'X':
			Console::Write("X");
			break;
		case 'Y':
			Console::Write("Y");
			break;
		case 'Z':
			Console::Write("Z");
			break;
			//параметр команды
		case 'P':
			Console::Write("P");
			break;
			//скорость рабочей подачи, для фрезерных милиметры в минуту, mm/min
		case 'F':
			Console::Write("F");
			break;
			//частота вращения шпинделя
		case 'S':
			Console::Write("S");
			break;
			//case R:	//не используется в этой версии, параметр стандартного цикла или радиус
			//case D:	//не используется в этой версии, параметр коррекции выбранного инструмента
			//case L:	//не используется в этой версии, число вызовов подпрограммы

			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси X.
		case 'I':
			Console::Write("I");
			break;
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси Y
		case 'J':
			Console::Write("J");
			break;
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние дуги по оси Z.
		case 'K':
			Console::Write("K");
			break;
			//Вспомогательные (технологические) команды
		case 'M':
			Console::Write("M");
			break;
			//номер инструмента
		case 'T':
			Console::Write("T");
			break;
		default:	//обработка нерегламентированных (ошибочных) значений
			Console::WriteLine("Wrong content in this \"" + str + "\" from index " + tmpindex);
			errorRows->Add(i);
			curindex = str->Length;
			i++;
			continue;
		}
		//достаем строку содержащую число
		String^ resultGetFloat = getFloat(str, tmpindex, curindex);
		Console::Write(resultGetFloat);
		//если строка пустая, не содержит символов, то есть, если начиная с конкретного символа нет чисел
		if (System::String::Empty->Equals(resultGetFloat)) {
			Console::WriteLine("not get float in this \"" + str + "\" from index " + tmpindex);
		}
		else {
			//если вместо строки вернуло nulptr, 
			//добавим номер этой строки в лист ошибочных строк, прекращаем работу с этой строкой
			if (resultGetFloat == nullptr) {
				Console::WriteLine(" Cannot get float (nulptr) in this \"" + str + "\" from index " + tmpindex);
				errorRows->Add(i);
				curindex = str->Length;
				i++;
				continue;
			}
			else
			{
				//проверки подстроки содержащей число пройдены, парсим
				if (!System::Single::TryParse(resultGetFloat, NumberStyles::AllowDecimalPoint,formatInfo , numParam))
							Console::WriteLine("Falture to TryParse for float");
			}
		}
		Console::WriteLine(" tmpindex: " + tmpindex + " curindex: " + curindex + " param: " + numParam);
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


