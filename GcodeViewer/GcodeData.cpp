#include "GcodeData.h"

using namespace GData;
using namespace System;
using namespace System::Collections;
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
	errorRows = gcnew System::Collections::Generic::List<Int32>(1);
}

GcodeData::~GcodeData()
{

}

//возвращает строку, содержащую первое число от символа заданной строки с заданным индексом,
//если такого числа нет, то возвращает nulptr
String ^ GData::GcodeData::getStartFloat(String ^str, int startIndex)
{
	int start = startIndex, end = startIndex;
	while (System::Char::IsLetter(str[start]) && start + 1 < str->Length)
	{
		start++;
		end++;
	}
	if(end < str->Length) ++end;
	while (end < str->Length && !System::Char::IsWhiteSpace(str[end]) && System::Char::IsNumber(str[end])) {
		end++;
	}
	Console::Write(" start: " + start + " end: " + end + " float " + str->Substring(start, end - start));
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

System::Collections::Generic::List<Polyline^>^ GData::GcodeData::tranlate(System::Collections::Generic::List<String^>^ cmds)
{
	//если коллекция пуста, то нечего и елать
	if (cmds == nullptr || cmds->Count < 1)
		return nullptr;
	//начальные состояния
	GData::GState gstate = GState::None;
	GData::Modal modalstate = Modal::None;

	System::Collections::Generic::List<Polyline^>^ lines;
	int i = 0;
	float numParam;
	//пройдемся по коллекции comds
	while (i < cmds->Count) {
		String^ str = gcnew String(cmds[i]);
		str = str->Trim();
		if (String::IsNullOrWhiteSpace(str)) {
			i++;
			continue;
		}
		switch (str[0]) {
			//Подготовительные (основные) команды
		case 'G':
			Console::Write("G");
			break;
		case 'X':
		case 'Y':
		case 'Z':
			//параметр команды
		case 'P':
			//скорость рабочей подачи, для фрезерных милиметры в минуту, mm/min
		case 'F':
			//частота вращения шпинделя
		case 'S':
			//case R:	//не используется в этой версии, параметр стандартного цикла или радиус
			//case D:	//не используется в этой версии, параметр коррекции выбранного инструмента
			//case L:	//не используется в этой версии, число вызовов подпрограммы

			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси X.
		case 'I':
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние от начальной точки до центра дуги по оси Y
		case 'J':
			//Параметр дуги при круговой интерполяции. Инкрементальное расстояние дуги по оси Z.
		case 'K':
			//Вспомогательные (технологические) команды
		case 'M':
			;
		case 'T': //номер инструмента
			break;
		default:	//обработка нерегламентированных (ошибочных) значений
			;
		}
		Console::Write(System::Single::TryParse(getStartFloat(str, 0), numParam));
		Console::WriteLine(numParam);
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


