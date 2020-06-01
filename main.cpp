#include <iostream>		// заголовочный файл библиотеки для работы с потоками ввода-вывода консоли
#include <locale>		// заголовочный файл библиотеки для работы с локалями
#include <vector>		// заголовочный файл библиотеки для работы с векторами
#include <fstream>		// заголовочный файл библиотеки для работы с файловыми потоками
#include <sstream>		// заголовочный файл библиотеки для работы с текстовыми потоками
#include <windows.h>	// заголовочный файл библиотеки для работы с WINAPI


using namespace std;	// подключение пространства имен std

#define CIN_FLUSH if (cin.peek()) cin.ignore() // макрос очистки потока ввода

class Contact {
    // приватные поля класса
	private:
		string surname;		// фамилия контакта
		string firstname; 	// имя контакта
		string telephone;	// телефон контакта

	// публичные поля класса
	public:
		// конструктор по умолчанию
		Contact() {}

		// конструктор с параметрами
		Contact(string _firstname, string _surname, string _telephone) {
			this->firstname = _firstname;
			this->surname = _surname;
			this->telephone = _telephone;
		}

		// деструктор
		~Contact() {}

		// сеттеры для полей класса
		void set_firstname(string _firstname) {
			firstname = _firstname;
		}

		void set_surname(string _surname) {
			surname = _surname;
		}

		void set_telephone(string _telephone) {
			telephone = _telephone;
		}

		// геттеры для полей класса
		string get_firstname() {
			return firstname;
		}

		string get_surname() {
			return surname;
		}

		string get_telephone() {
			return telephone;
		}
};

vector <Contact> phoneBook;	// вектор для хранения контактов (телефонная книга)

// функция получения контактов из файла
void getContactsFromFile() {
	system("cls"); // очистка консоли

	phoneBook.clear(); // очищаем телефонную книгу

	ifstream fin("contacts.txt"); 	// открываем файл с контактами для чтения
	string line;					// строка для считывания контактов из файла
	Contact contact; 				// объект для записи в него контакта
	string attr;					// переменная для получения данных контакта из тектстового потока

	if(!fin.is_open()) {
		cerr << "ОШИБКА: не удалось открыть файл для получения контактов..." << endl;
		exit(EXIT_FAILURE); // завершение программы с ошибкой
	} else {
		while(getline(fin, line)) { // читаем по одному контакту
			stringstream ss(line);	// делаем из строки строковый поток

			// переносим из строкового потока данные в объект
			ss >> attr; contact.set_surname(attr);
			ss >> attr; contact.set_firstname(attr);
			ss >> attr; contact.set_telephone(attr);

			// записываем объект в телефонный справочник
			phoneBook.push_back(contact);
		}

		fin.close(); // закрытие файла

		cout << "Контакты были загружены из файла..." << endl << endl;
	}
}

// функция сохранения контактов в файл
void writeContactsInFile() {
	system("cls"); // очистка консоли

	ofstream fout("contacts.txt");	// открываем файл с контактами на запись
	string contact;	// переменная для записи контакта

	if(!fout.is_open()) {
		cerr << "ОШИБКА: не удалось открыть файл для сохранения контактов..." << endl;
		exit(EXIT_FAILURE); // завершение программы с ошибкой
	} else {
		// пробегаем по всем контактам из телефонного справочника
		for(Contact c : phoneBook) {
			// формируем строку контакта
			contact = c.get_surname();
			contact += " ";
			contact += c.get_firstname();
			contact += " ";
			contact += c.get_telephone();

			// записываем строку в файл
			fout << contact << endl;
		}

		fout.close(); // закрытие файла

		cout << "Контакты были сохранены в файл..." << endl << endl;
	}
}

// функция вывода списка контактов в консоль
void printContacts() {
	system("cls"); // очистка консоли

	int number = 0; // переменная для нумерации контактов

	if(phoneBook.size()) { // если в тел. справочнике есть контакты
		cout << "=========================================================" << endl;
		cout << "= №\tФамилия\t\tИмя\t\tТелефон\t\t=" << endl;
		cout << "=========================================================" << endl;
		// пробегаем по всем контактам из телефонного справочника
		for (Contact c : phoneBook) {
			cout << "= " << (++number) << ".\t";
			cout << c.get_surname() << "\t";
			if(c.get_surname().length() < 8) cout << "\t";
			cout << c.get_firstname() << "\t";
			if(c.get_firstname().length() < 8) cout << "\t";
			cout << c.get_telephone() << "\t";
			if(c.get_telephone().length() < 8) cout << "\t";
			cout << "=" << endl;
		}
		cout << "=========================================================" << endl << endl;
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl;
	}
	cout << endl;
}

// функция добавления нового контакта
void addContact() {
	system("cls"); // очистка консоли

	string attr; // переменная для получения данных контакта из консоли
	Contact c;	// объект для создания контакта

	CIN_FLUSH; // очистка потока ввода

	cout << "Создание нового контакта..." << endl << endl;
	cout << "Фамилия: "; getline(cin, attr);
	c.set_surname(attr);
	cout << "Имя: "; getline(cin, attr);
	c.set_firstname(attr);
	cout << "Телефон: "; getline(cin, attr);
	c.set_telephone(attr);

	phoneBook.push_back(c);

	cout << endl << "Контакт был добавлен..." << endl << endl;
}

// функция редактирования контакта
void editContact() {
	system("cls"); // очистка консоли

	int num; // номер контакта, который редактируем
	Contact c; // объект для редактирования контакта
	string attr; // переменная для получения данных контакта из консоли

	// если в телефонном справочнике есть контакты
	if(phoneBook.size()) {
		printContacts();
		cout << "Введите номер контакта, который хотите отредактировать: ";
		cin >> num;

		cout << endl;
		if(num > 0 && num <= phoneBook.size()) { // введен допустимый номер контакта
			CIN_FLUSH; // очистка потока ввода

			cout << "Фамилия: "; getline(cin, attr);
			c.set_surname(attr);
			cout << "Имя: "; getline(cin, attr);
			c.set_firstname(attr);
			cout << "Телефон: "; getline(cin, attr);
			c.set_telephone(attr);

			phoneBook[num - 1] = c;

			cout << endl << "Контакт был изменен..." << endl << endl;
		} else {
			cout << "Введен некорректный номер контакта..." << endl << endl;
		}
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl << endl;
	}
}

// функция удаления контакта
void deleteContact() {
	system("cls"); // очистка консоли

	int num; // номер контакта, который удаляем

	// если в телефонном справочнике есть контакты
	if(phoneBook.size()) {
		printContacts();
		cout << "Введите номер контакта, который хотите удалить: ";
		cin >> num;

		cout << endl;
		if(num > 0 && num <= phoneBook.size()) { // введен допустимый номер контакта

			auto first = phoneBook.cbegin(); // указатель на первый контакт
			phoneBook.erase(first + num - 1);   // удаляем контакт, с номером num

			cout << "Контакт был удален..." << endl << endl;
		} else {
			cout << "Введен некорректный номер контакта..." << endl << endl;
		}
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl << endl;
	}
}

// функция удаления всех контактов
void deleteContacts() {
	system("cls"); // очистка консоли

	// если в телефонном справочнике есть контакты
	if(phoneBook.size()) {
		phoneBook.clear(); // удаляем все контакты
		cout << "Все контакты были удалены..." << endl << endl;
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl << endl;
	}
}

// функция поиска контактов по фамилии
void searchSurname() {
	system("cls"); // очистка консоли

	string surname; // переменная для ввода фамилии
	bool match = false; // переменная, показывающая нашлись ли контакты
	int number;	// переменная для нумерации найденных контактов

	// если в телефонном справочнике есть контакты
	if(phoneBook.size()) {
		CIN_FLUSH; // очистка потока ввода

		cout << "Введите фамилию для поиска: ";
		getline(cin, surname);

		cout << endl << "Совпадения:" << endl;

		// пробегаем по всем контактам из телефонного справочника
		for (Contact c : phoneBook) {
			if (c.get_surname().find(surname) != string::npos) {
				match = true;
				cout << (++number) << ". ";
				cout << c.get_surname() << " ";
				cout << c.get_firstname() << " ";
				cout << c.get_telephone() << endl;
			}
		}
		if(!match) {
			cout << "не найдены..." << endl;
		}
		cout << endl;
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl << endl;
	}
}

// функция поиска контактов по телефону
void searchTelephone() {
	system("cls"); // очистка консоли

	string telephone; // переменная для ввода телефона
	bool match = false; // переменная, показывающая нашлись ли контакты
	int number;	// переменная для нумерации найденных контактов

	// если в телефонном справочнике есть контакты
	if(phoneBook.size()) {
		CIN_FLUSH; // очистка потока ввода

		cout << "Введите телефон для поиска: ";
		getline(cin, telephone);

		cout << endl << "Совпадения:" << endl;

		// пробегаем по всем контактам из телефонного справочника
		for (Contact c : phoneBook) {
			if (c.get_telephone().find(telephone) != string::npos) {
				match = true;
				cout << (++number) << ". ";
				cout << c.get_surname() << " ";
				cout << c.get_firstname() << " ";
				cout << c.get_telephone() << endl;
			}
		}
		if(!match) {
			cout << "не найдены..." << endl;
		}
		cout << endl;
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl << endl;
	}
}

// функция поиска контактов по имени
void searchFirstname() {
	system("cls"); // очистка консоли

	string firstname; // переменная для ввода имени
	bool match = false; // переменная, показывающая нашлись ли контакты
	int number;	// переменная для нумерации найденных контактов

	// если в телефонном справочнике есть контакты
	if(phoneBook.size()) {
		CIN_FLUSH; // очистка потока ввода

		cout << "Введите имя для поиска: ";
		getline(cin, firstname);

		cout << endl << "Совпадения:" << endl;

		// пробегаем по всем контактам из телефонного справочника
		for (Contact c : phoneBook) {
			if (c.get_firstname().find(firstname) != string::npos) {
				match = true;
				cout << (++number) << ". ";
				cout << c.get_surname() << " ";
				cout << c.get_firstname() << " ";
				cout << c.get_telephone() << endl;
			}
		}
		if(!match) {
			cout << "не найдены..." << endl;
		}
		cout << endl;
	} else {
		cout << "В телефонном справочнике нет ни одного контакта..." << endl << endl;
	}
}

void menu() {
	cout << "#########################################################" << endl;
	cout << "################# ТЕЛЕФОННЫЙ СПРАВОЧНИК #################" << endl;
	cout << "#########################################################" << endl;
	cout << "###################- МЕНЮ ПРОГРАММЫ -####################" << endl;
	cout << "#########################################################" << endl;
	cout << "          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "          |> 1.   Загрузить данные из файла   |" << endl;
	cout << "          |> 2.   Сохранить данные в файл     |" << endl;
	cout << "          |> 3.   Просмотреть контакты        |" << endl;
	cout << "          |> 4.   Добавить контакт            |" << endl;
	cout << "          |> 5.   Изменить контакт            |" << endl;
	cout << "          |> 6.   Удалить контакт             |" << endl;
	cout << "          |> 7.   Удалить весь список!        |" << endl;
	cout << "          |> 8.   Поиск контакта по фамилии   |" << endl;
	cout << "          |> 9.   Поиск контакта по имени     |" << endl;
	cout << "          |> 10.  Поиск контакта по номеру    |" << endl;
	cout << "          |> 0.   Выход из программы          |" << endl;
	cout << "          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	cout << "\t       Введите пукнт меню  > ";
}

int main () {
    system("mode con cols=58 lines=50");//установка размера консоли
    system("color 1F"); //установка цвета консоли и шрифта
	setlocale(0, ""); // установка локали по умолчанию

	// установка кодировок для ввода/вывода консоли
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	int choice; // переменная для выбора пунктов меню

	do {
		menu(); // выводим меню
		cin >> choice; // пользователь выбирает пункт меню

		switch(choice) {
			case 1: {	// получение контактов из файла
				getContactsFromFile();
				break;
			}
			case 2: {	// запись контактов в файл
				writeContactsInFile();
				break;
			}
			case 3: {	// вывод списка контактов в консоль
				printContacts();
				break;
			}
			case 4: {	// добавление нового контакта
				addContact();
				break;
			}
			case 5: {	// редактирование контакта
				editContact();
				break;
			}
			case 6: {	// удаление контакта
				deleteContact();
				break;
			}
			case 7: {	// удаление всех контактов
				deleteContacts();
				break;
			}
			case 8: {	// поиск контакта по фамилии
				searchSurname();
				break;
			}
			case 9: {	// поиск контакта по имени
				searchFirstname();
				break;
			}
			case 10: {	// поиск контакта по телефону
				searchTelephone();
				break;
			}
			case 0: {
				system("cls"); // очистка консоли
				cout << "Завершение работы с программой..." << endl;
				cin.get();
				return EXIT_SUCCESS; // успешное завершение главной функции
			}
		}
	} while(true);

}
