#include <iostream>		// ������������ ���� ���������� ��� ������ � �������� �����-������ �������
#include <locale>		// ������������ ���� ���������� ��� ������ � ��������
#include <vector>		// ������������ ���� ���������� ��� ������ � ���������
#include <fstream>		// ������������ ���� ���������� ��� ������ � ��������� ��������
#include <sstream>		// ������������ ���� ���������� ��� ������ � ���������� ��������
#include <windows.h>	// ������������ ���� ���������� ��� ������ � WINAPI


using namespace std;	// ����������� ������������ ���� std

#define CIN_FLUSH if (cin.peek()) cin.ignore() // ������ ������� ������ �����

class Contact {
    // ��������� ���� ������
	private:
		string surname;		// ������� ��������
		string firstname; 	// ��� ��������
		string telephone;	// ������� ��������

	// ��������� ���� ������
	public:
		// ����������� �� ���������
		Contact() {}

		// ����������� � �����������
		Contact(string _firstname, string _surname, string _telephone) {
			this->firstname = _firstname;
			this->surname = _surname;
			this->telephone = _telephone;
		}

		// ����������
		~Contact() {}

		// ������� ��� ����� ������
		void set_firstname(string _firstname) {
			firstname = _firstname;
		}

		void set_surname(string _surname) {
			surname = _surname;
		}

		void set_telephone(string _telephone) {
			telephone = _telephone;
		}

		// ������� ��� ����� ������
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

vector <Contact> phoneBook;	// ������ ��� �������� ��������� (���������� �����)

// ������� ��������� ��������� �� �����
void getContactsFromFile() {
	system("cls"); // ������� �������

	phoneBook.clear(); // ������� ���������� �����

	ifstream fin("contacts.txt"); 	// ��������� ���� � ���������� ��� ������
	string line;					// ������ ��� ���������� ��������� �� �����
	Contact contact; 				// ������ ��� ������ � ���� ��������
	string attr;					// ���������� ��� ��������� ������ �������� �� ����������� ������

	if(!fin.is_open()) {
		cerr << "������: �� ������� ������� ���� ��� ��������� ���������..." << endl;
		exit(EXIT_FAILURE); // ���������� ��������� � �������
	} else {
		while(getline(fin, line)) { // ������ �� ������ ��������
			stringstream ss(line);	// ������ �� ������ ��������� �����

			// ��������� �� ���������� ������ ������ � ������
			ss >> attr; contact.set_surname(attr);
			ss >> attr; contact.set_firstname(attr);
			ss >> attr; contact.set_telephone(attr);

			// ���������� ������ � ���������� ����������
			phoneBook.push_back(contact);
		}

		fin.close(); // �������� �����

		cout << "�������� ���� ��������� �� �����..." << endl << endl;
	}
}

// ������� ���������� ��������� � ����
void writeContactsInFile() {
	system("cls"); // ������� �������

	ofstream fout("contacts.txt");	// ��������� ���� � ���������� �� ������
	string contact;	// ���������� ��� ������ ��������

	if(!fout.is_open()) {
		cerr << "������: �� ������� ������� ���� ��� ���������� ���������..." << endl;
		exit(EXIT_FAILURE); // ���������� ��������� � �������
	} else {
		// ��������� �� ���� ��������� �� ����������� �����������
		for(Contact c : phoneBook) {
			// ��������� ������ ��������
			contact = c.get_surname();
			contact += " ";
			contact += c.get_firstname();
			contact += " ";
			contact += c.get_telephone();

			// ���������� ������ � ����
			fout << contact << endl;
		}

		fout.close(); // �������� �����

		cout << "�������� ���� ��������� � ����..." << endl << endl;
	}
}

// ������� ������ ������ ��������� � �������
void printContacts() {
	system("cls"); // ������� �������

	int number = 0; // ���������� ��� ��������� ���������

	if(phoneBook.size()) { // ���� � ���. ����������� ���� ��������
		cout << "=========================================================" << endl;
		cout << "= �\t�������\t\t���\t\t�������\t\t=" << endl;
		cout << "=========================================================" << endl;
		// ��������� �� ���� ��������� �� ����������� �����������
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
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl;
	}
	cout << endl;
}

// ������� ���������� ������ ��������
void addContact() {
	system("cls"); // ������� �������

	string attr; // ���������� ��� ��������� ������ �������� �� �������
	Contact c;	// ������ ��� �������� ��������

	CIN_FLUSH; // ������� ������ �����

	cout << "�������� ������ ��������..." << endl << endl;
	cout << "�������: "; getline(cin, attr);
	c.set_surname(attr);
	cout << "���: "; getline(cin, attr);
	c.set_firstname(attr);
	cout << "�������: "; getline(cin, attr);
	c.set_telephone(attr);

	phoneBook.push_back(c);

	cout << endl << "������� ��� ��������..." << endl << endl;
}

// ������� �������������� ��������
void editContact() {
	system("cls"); // ������� �������

	int num; // ����� ��������, ������� �����������
	Contact c; // ������ ��� �������������� ��������
	string attr; // ���������� ��� ��������� ������ �������� �� �������

	// ���� � ���������� ����������� ���� ��������
	if(phoneBook.size()) {
		printContacts();
		cout << "������� ����� ��������, ������� ������ ���������������: ";
		cin >> num;

		cout << endl;
		if(num > 0 && num <= phoneBook.size()) { // ������ ���������� ����� ��������
			CIN_FLUSH; // ������� ������ �����

			cout << "�������: "; getline(cin, attr);
			c.set_surname(attr);
			cout << "���: "; getline(cin, attr);
			c.set_firstname(attr);
			cout << "�������: "; getline(cin, attr);
			c.set_telephone(attr);

			phoneBook[num - 1] = c;

			cout << endl << "������� ��� �������..." << endl << endl;
		} else {
			cout << "������ ������������ ����� ��������..." << endl << endl;
		}
	} else {
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl << endl;
	}
}

// ������� �������� ��������
void deleteContact() {
	system("cls"); // ������� �������

	int num; // ����� ��������, ������� �������

	// ���� � ���������� ����������� ���� ��������
	if(phoneBook.size()) {
		printContacts();
		cout << "������� ����� ��������, ������� ������ �������: ";
		cin >> num;

		cout << endl;
		if(num > 0 && num <= phoneBook.size()) { // ������ ���������� ����� ��������

			auto first = phoneBook.cbegin(); // ��������� �� ������ �������
			phoneBook.erase(first + num - 1);   // ������� �������, � ������� num

			cout << "������� ��� ������..." << endl << endl;
		} else {
			cout << "������ ������������ ����� ��������..." << endl << endl;
		}
	} else {
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl << endl;
	}
}

// ������� �������� ���� ���������
void deleteContacts() {
	system("cls"); // ������� �������

	// ���� � ���������� ����������� ���� ��������
	if(phoneBook.size()) {
		phoneBook.clear(); // ������� ��� ��������
		cout << "��� �������� ���� �������..." << endl << endl;
	} else {
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl << endl;
	}
}

// ������� ������ ��������� �� �������
void searchSurname() {
	system("cls"); // ������� �������

	string surname; // ���������� ��� ����� �������
	bool match = false; // ����������, ������������ ������� �� ��������
	int number;	// ���������� ��� ��������� ��������� ���������

	// ���� � ���������� ����������� ���� ��������
	if(phoneBook.size()) {
		CIN_FLUSH; // ������� ������ �����

		cout << "������� ������� ��� ������: ";
		getline(cin, surname);

		cout << endl << "����������:" << endl;

		// ��������� �� ���� ��������� �� ����������� �����������
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
			cout << "�� �������..." << endl;
		}
		cout << endl;
	} else {
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl << endl;
	}
}

// ������� ������ ��������� �� ��������
void searchTelephone() {
	system("cls"); // ������� �������

	string telephone; // ���������� ��� ����� ��������
	bool match = false; // ����������, ������������ ������� �� ��������
	int number;	// ���������� ��� ��������� ��������� ���������

	// ���� � ���������� ����������� ���� ��������
	if(phoneBook.size()) {
		CIN_FLUSH; // ������� ������ �����

		cout << "������� ������� ��� ������: ";
		getline(cin, telephone);

		cout << endl << "����������:" << endl;

		// ��������� �� ���� ��������� �� ����������� �����������
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
			cout << "�� �������..." << endl;
		}
		cout << endl;
	} else {
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl << endl;
	}
}

// ������� ������ ��������� �� �����
void searchFirstname() {
	system("cls"); // ������� �������

	string firstname; // ���������� ��� ����� �����
	bool match = false; // ����������, ������������ ������� �� ��������
	int number;	// ���������� ��� ��������� ��������� ���������

	// ���� � ���������� ����������� ���� ��������
	if(phoneBook.size()) {
		CIN_FLUSH; // ������� ������ �����

		cout << "������� ��� ��� ������: ";
		getline(cin, firstname);

		cout << endl << "����������:" << endl;

		// ��������� �� ���� ��������� �� ����������� �����������
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
			cout << "�� �������..." << endl;
		}
		cout << endl;
	} else {
		cout << "� ���������� ����������� ��� �� ������ ��������..." << endl << endl;
	}
}

void menu() {
	cout << "#########################################################" << endl;
	cout << "################# ���������� ���������� #################" << endl;
	cout << "#########################################################" << endl;
	cout << "###################- ���� ��������� -####################" << endl;
	cout << "#########################################################" << endl;
	cout << "          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "          |> 1.   ��������� ������ �� �����   |" << endl;
	cout << "          |> 2.   ��������� ������ � ����     |" << endl;
	cout << "          |> 3.   ����������� ��������        |" << endl;
	cout << "          |> 4.   �������� �������            |" << endl;
	cout << "          |> 5.   �������� �������            |" << endl;
	cout << "          |> 6.   ������� �������             |" << endl;
	cout << "          |> 7.   ������� ���� ������!        |" << endl;
	cout << "          |> 8.   ����� �������� �� �������   |" << endl;
	cout << "          |> 9.   ����� �������� �� �����     |" << endl;
	cout << "          |> 10.  ����� �������� �� ������    |" << endl;
	cout << "          |> 0.   ����� �� ���������          |" << endl;
	cout << "          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	cout << "\t       ������� ����� ����  > ";
}

int main () {
    system("mode con cols=58 lines=50");//��������� ������� �������
    system("color 1F"); //��������� ����� ������� � ������
	setlocale(0, ""); // ��������� ������ �� ���������

	// ��������� ��������� ��� �����/������ �������
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	int choice; // ���������� ��� ������ ������� ����

	do {
		menu(); // ������� ����
		cin >> choice; // ������������ �������� ����� ����

		switch(choice) {
			case 1: {	// ��������� ��������� �� �����
				getContactsFromFile();
				break;
			}
			case 2: {	// ������ ��������� � ����
				writeContactsInFile();
				break;
			}
			case 3: {	// ����� ������ ��������� � �������
				printContacts();
				break;
			}
			case 4: {	// ���������� ������ ��������
				addContact();
				break;
			}
			case 5: {	// �������������� ��������
				editContact();
				break;
			}
			case 6: {	// �������� ��������
				deleteContact();
				break;
			}
			case 7: {	// �������� ���� ���������
				deleteContacts();
				break;
			}
			case 8: {	// ����� �������� �� �������
				searchSurname();
				break;
			}
			case 9: {	// ����� �������� �� �����
				searchFirstname();
				break;
			}
			case 10: {	// ����� �������� �� ��������
				searchTelephone();
				break;
			}
			case 0: {
				system("cls"); // ������� �������
				cout << "���������� ������ � ����������..." << endl;
				cin.get();
				return EXIT_SUCCESS; // �������� ���������� ������� �������
			}
		}
	} while(true);

}
