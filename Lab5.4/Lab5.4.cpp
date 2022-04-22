/*
Описати структуру з ім’ям Note, що містить наступні поля:
прізвище, ім’я;
номер телефону;
день народження (масив з трьох чисел).
Написати програму, що виконує наступні дії:
введення даних з клавіатури у файл, що складається з елементів типу Note;
впорядкування записів за датами днів народження;
виведенняна  екран  інформації  про  людину,  номер  телефону  якої  введений  з клавіатури;  якщо  такої  людини  немає,  вивести  на  екран  відповідне повідомлення.
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct Note {
	char fullName[64];
	char phoneNum[64];
	int birthDate[3];
};


void Create(const char* fName);
void Print(const char* fName);
void fWrite(fstream& f, const int i, Note x);
Note fRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void Sort(const char* fName);
int phoneSearch(const char* fName, char userStr[]);



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char f[64];
	char g[6] = "g.dat";
	char prizv[64];
	int kurs, gradePhys, binNum;

	int menuItem;
	do {
		cout << "Оберіть дію: " << endl;
		cout << "[1]  введення даних з клавіатури." << endl;
		cout << "[2]  вивід даних на екран." << endl;
		cout << "[3]  сортувати масив за заданими ключами(фізичне сортування)." << endl;
		cout << "[4]  пошук за номером телефона." << endl;
		cout << "[5]  ввести назву файла." << endl;
		cout << "[0]  вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		switch (menuItem) {
		case 1:
			Create(f);
			break;
		case 2:
			Print(f);
			break;
		case 3:
			Sort(f);
			break;
		case 4:
			char phone[64];
			cout << "Ввведіть номер, який бажаєте знайти: ";
			cin >> phone;
			phoneSearch(f, phone);
			break;
		case 5:
			cout << "Введіть назву файла: "; cin >> f;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилковезначення! Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);



	system("pause");
	cin.get();
	return 0;
}

void Create(const char* fName)
{
	ofstream f(fName, ios::binary);
	Note note;
	char ch;
	int i = 1;
	do {
		cout << "Нотатка №: " << i++ << ": " << endl;
		cin.ignore();
		cout << "Прізвище та ім'я: ";
		cin >> note.fullName;
		cout << "Номер телефону: ";
		cin >> note.phoneNum;
		cout << "День народження: "; cin >> note.birthDate[0];
		cout << "Місця народження: "; cin >> note.birthDate[1];
		cout << "Рік народження: "; cin >> note.birthDate[2];
		cout << endl;

		cout << endl;
		if (!f.write((char*)&note, sizeof(Note))) {
			cerr << "Error writing file." << endl;
		}
		cout << "Continue?(Y/N)"; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}



void Print(const char* fName)
{
	cout << "======================================================================================" << endl;
	cout << "|  No  |    Прізвище та ім'я    |  Номер телефону  |      Повна дата народження      |" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;

	ifstream f(fName, ios::binary);
	Note note;
	int i = 1;
	while (f.read((char*)&note, sizeof(Note))) {
		cout << "| " << setw(3) << right << i++ << "  ";
		cout << "| " << setw(23) << left << note.fullName
			<< "|  " << setw(16) << right << note.phoneNum
			<< "|  " << setfill('0') << setw(2) << note.birthDate[0] << "." << setfill('0') << setw(2) << note.birthDate[1] << "." << note.birthDate[2] << setfill(' ') << setw(22) << " |" << endl;

	}
	cout << "======================================================================================" << endl;
	cout << endl;
}



void fWrite(fstream& f, const int i, Note x) {
	f.seekp(i * (long)sizeof(Note));
	f.write((char*)&x, sizeof(Note));
}

Note fRead(fstream& f, const int i) {
	Note x;
	f.seekg(i * (long)sizeof(Note));
	f.read((char*)&x, sizeof(Note));
	return x;
}

void fChange(fstream& f, const int i, const int j) {
	Note x = fRead(f, i);
	Note y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}

void Sort(const char* fName) {
	fstream f(fName, ios::binary | ios::in | ios::out);

	f.seekg(0, ios::end);
	int size = f.tellg() / sizeof(Note);
	f.seekg(0, ios::beg);

	for (int i0 = 1; i0 < size; i0++) {
		for (int i1 = 0; i1 < size - i0; i1++) {
			Note a = fRead(f, i1);
			Note b = fRead(f, i1 + 1);
			if (((a.birthDate[2] > b.birthDate[2]) ||
				(a.birthDate[2] == b.birthDate[2] && a.birthDate[1] > b.birthDate[1]) ||
				(a.birthDate[2] == b.birthDate[2] && a.birthDate[1] == b.birthDate[1] && a.birthDate[0] > b.birthDate[0]))) {
				fChange(f, i1, i1 + 1);
			}
		}
	}


	f.seekp(0, ios::end);
}

int phoneSearch(const char* fName, char userStr[]) {
	ifstream f(fName, ios::binary);
	Note note;
	int n = 1;
	
	cout <<endl<< "======================================================================================" << endl;
	cout << "|  No  |    Прізвище та ім'я    |  Номер телефону  |      Повна дата народження      |" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;

	while (f.read((char*)&note, sizeof(Note))) {
		if (strcmp(note.phoneNum, userStr) == 0) {
			cout << endl;
			cout << "| " << setw(3) << right << n++ << "  ";
			cout << "| " << setw(23) << left << note.fullName
				<< "|  " << setw(16) << right << note.phoneNum
				<< "|  " << setfill('0') << setw(2) << note.birthDate[0] << "." << setfill('0') << setw(2) << note.birthDate[1] << "." << note.birthDate[2] << setfill(' ') << setw(22) << " |" << endl;

		}
	}

	cout << "======================================================================================" << endl;
	cout << endl;

	if (n == 1) {
		cout << endl;
		cout << "Cпівпадінь за введеними даними не знайдено." << endl << endl;
		return -1;
	}
	else {
		return 1;
	}
}