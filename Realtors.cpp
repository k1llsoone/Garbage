// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//
#include "pch.h"
#include <iostream>
#include <stack>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iomanip>

using namespace std;

class Realtor {

private:
	string fname;
	string sname;

public:
	int realtorId;
	string realtor_firstName;
	string realtor_lastName;
	Realtor();
	Realtor(int id, string name, string surname);
	int GetId();
	string GetName();
	string GetSurname();
};

Realtor::Realtor() {
	fname = "Максим";
	sname = "Королев";
	realtorId = '1';

}

Realtor::Realtor(int id, string name, string surname) {
	fname = name;
	realtorId = id;
	sname = surname;
}

int Realtor::GetId() { return realtorId; }
string Realtor::GetName() { return fname; }
string Realtor::GetSurname() { return sname; }


class Estate {

private:
	string name;
	int type;

public:
	Estate();
	Estate(int id, int ty, string n);
	int estateId;
	string adress;
	bool is_apartment;
	bool is_house;
	bool for_rent;
	bool in_rent;
	bool for_sale;
	bool sold_out;
	int price;
	int GetId();
	string GetName();
	int GetType();
};

Estate::Estate() {
	estateId = '1';
	name = "Квартира1";
	type = 1;
}

Estate::Estate(int id, int ty, string n) {//Конструктор с параметрами (параметры - данные из файла)
	estateId = id;
	name = n;
	type = ty;
}

int Estate::GetId() { return estateId; }
string Estate::GetName() { return name; }
int Estate::GetType() { return type; }


class Client {
public:
	int clientId;
	string fname;
	string sname;
	int realtorId;
	int estateId;
	Client(const stack<Realtor>*realtors, const stack<Estate>*estates, int iter);
	string GenerateName();
	string GenerateSurname();
	void Print();
};
Client::Client(const stack<Realtor>*realtors, const stack<Estate>*estates, int iter) {

	fname = GenerateName();
	sname = GenerateSurname();
	clientId = iter;

	
	stack<Realtor> rtemp;
	Realtor realtor;
	rtemp = *realtors;
	realtor = rtemp.top();
	realtorId = realtor.GetId();
	
	rtemp.pop();

	
	stack<Estate> etemp;
	Estate estate;
	etemp = *estates;
	estate = etemp.top();
	estateId = estate.GetId();
	
	etemp.pop();
}

void Client::Print() {
	cout << "ID: " << clientId << "; Name: " << fname << "; Surname: " << sname << "; Realtor: " << realtorId << "; Estate: " << estateId << endl;
}

string Client::GenerateName() {
	string names[] = { "Артем", "Борис", "Виктор", "Александр", "Жанна",
					   "Екатерина","Валерия","Владимир","Роман","Лидия",
					   "Татьяна","Станислав","Андрей","Александра", "Елена", };
	return names[rand()%14+1];
}
string Client::GenerateSurname() {
	string names[] = { "Борисов(а)", "Очхикидзе", "Пличенко", "Иванов(а)", "Шпотин(а)",
				   "Сагилян","Золотарёв(а)","Петров(а)","Нурмидзе","Сахно",
				   "Доценко","Кищук","Сидоров(а)","Христо", "Епремян", };
	return names[rand() % 14 + 1];
}

bool StrToBool(string var) {
	if (var == "true")
		return true;
	else
		return false;
}

int stringToInt(string s) {
	int result = 0;

	for (int i = 0; i < s.size(); i++)      
	{
		int digit = s[i] - '0';
		result = 10 * result + digit;
	}

	return result;
}

stack<Realtor> GetRealtors() {

	stack<Realtor> Realtors;
	Realtor buff_Realtor;

	string realtors_file_path = "realtors.txt";

	string element = "";
	string buf;
	int array_position = 0;
	ifstream fin(realtors_file_path);

	while (!fin.eof()) {
		getline(fin, buf);
		int len = buf.length();
		element = "";

		for (int j = 0; j < len; j++) {
			if (buf[j] != '|') {
				element = element + buf[j];
			}
			else
			{
				array_position++;
				switch (array_position) {
				case 1:
					buff_Realtor.realtorId = stringToInt(element);
					element = "";
					break;
				case 2:
					buff_Realtor.realtor_firstName = element;
					element = "";
					break;
				case 3:
					buff_Realtor.realtor_lastName = element;
					element = "";
					break;
				case 4:
					Realtors.push(buff_Realtor);
					array_position = 0;
					element = "";
					break;
				}
			}
		}
	}

	fin.close();
	return Realtors;
}

stack<Estate> GetEstates() {

	stack<Estate> Real_estates;
	Estate buff_Estates;

	string estates_file_path = "real_estates.txt";

	string element = "";
	string buf;
	int array_position = 0;
	ifstream fin(estates_file_path);

	while (!fin.eof()) {
		getline(fin, buf);
		int len = buf.length();
		element = "";

		for (int j = 0; j < len; j++) {
			if (buf[j] != '|') {
				element = element + buf[j];
			}
			else
			{
				array_position++;
				switch (array_position) {
				case 1:
					buff_Estates.estateId = stringToInt(element);
					element = "";
					break;
				case 2:
					buff_Estates.adress = element;
					element = "";
					break;
				case 3:
					buff_Estates.price = stringToInt(element);
					element = "";
					break;
				case 4:
					buff_Estates.is_apartment = StrToBool(element);
					element = "";
					break;
				case 5:
					buff_Estates.is_house = StrToBool(element);
					element = "";
					break;
				case 6:
					buff_Estates.for_rent = StrToBool(element);
					element = "";
					break;
				case 7:
					buff_Estates.in_rent = StrToBool(element);
					element = "";
					break;
				case 8:
					buff_Estates.for_sale = StrToBool(element);
					element = "";
					break;
				case 9:
					buff_Estates.sold_out = StrToBool(element);
					Real_estates.push(buff_Estates);
					array_position = 0;
					element = "";
					break;
				}
			}
		}
	}

	fin.close();
	return Real_estates;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	srand(time(NULL));
	
	string ftemp = "clients_temp.txt";

	string ftemp_clients = "clients.txt";

	char* buffer;

	stack<Realtor> realtorsAll;
	stack<Estate> estatesAll;
	stack<Client> clientsAll;

	realtorsAll = GetRealtors();
	estatesAll = GetEstates();


	const stack<Realtor>* rLink = &realtorsAll;
	const stack<Estate>* eLink = &estatesAll;


	if (realtorsAll.empty() == false && estatesAll.empty() == false) {
		for (int i = 30; i >= 1; i--) {
			Client client(rLink, eLink, i);
			if (clientsAll.empty() == true) {
				clientsAll.emplace(client);
			}
			else {
				clientsAll.push(client);
			}
		}
	}

	ifstream file(ftemp);
	if (!file.is_open()) {
		ofstream file(ftemp);
	}

	//Запись в файл и вывод в консоль
	if (clientsAll.empty() == false) {
		ofstream clientsFile(ftemp_clients, ios_base::out | ios_base::trunc);
		if (!clientsFile.is_open()) {
			cout << "Файл не может быть открыт.\n";
		}
		for (int i = 1; i <= (int)clientsAll.size(); i++) {
			Client client = clientsAll.top();
			clientsFile << "День №: " << i << " | " << "ID клиента " << client.clientId << endl;
			clientsFile << client.fname << " " << client.sname << " приобрёл недвижимость с ID: " << client.estateId << " у риелтора с ID: " << client.realtorId << endl;
			client.Print();
			clientsAll.pop();
		}
		clientsFile.close();
	}
	cin.get();
	return EXIT_SUCCESS;
}
