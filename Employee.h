#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include "Restaurant.h"
#include <conio.h>
using namespace std;

// Fix error, as the classes are interlinked
class Restaurant;
class Employee;
string getPassword();
class Employee {
public:
	// VARIABLES
	static int IDcounter;
	int ID;
	string name;
	string email;
	string password;
	Restaurant* workplace;
	bool type; // 0 means regular employee, 1 means manager

	Employee() = default;
	Employee(string name, string email, string password) 
	{
		this->name = name;
		this->password = password;
		this->email = email;
	}

	static bool isPasswordValid(string password) 
	{
		int length = password.size();
		bool isLengthMin, isSmall, isBig, isLengthMax, isSpecial, isNumber;
		isLengthMax = 0, isLengthMin = 0, isSmall = 0, isBig = 0, isSpecial = 0, isNumber = 0;
		if (length >= 8 && length <= 12) {
			isLengthMax = true;
			isLengthMin = true;
		}


		for (int i = 0; i < password.size(); i++) {
			char ch = password[i];
			if (ch >= 'a' && ch <= 'z') {
				isSmall = true;
				continue;
			}
			if (ch >= 'A' && ch <= 'Z') {
				isBig = true;
				continue;
			}
			if (ch >= '0' && ch <= '9') {
				isNumber = true;
				continue;
			}
			isSpecial = true;
		}

		return isLengthMax && isLengthMin && isSmall && isBig && isSpecial;
	}

	// A function that lets you edit your account details
	void EditAccountDetails() {

		cout << liner;
		cout << "What account details do you wish to change" << endl;
		cout << "1. Name" << endl;
		cout << "2. Password" << endl;
		int editChoice;
		do {
			cin >> editChoice;
		} while (editChoice < 1 || editChoice > 2);

		if (editChoice == 1) {
			cin.ignore();
			cout << "Enter your new name: ";
			getline(cin, name);
		}
		else {
			do {
				password = getPassword();

			} while (!isPasswordValid(password));
		}
	}
};
string getPassword() 
{
	string password;
	char ch;

	cout << "Enter your password: ";
	while (true) {
		ch = _getch(); // Read a character without echoing it to the console
		if (ch == '\r') { // Check for Enter key (carriage return)
			cout << endl; // Move to the next line
			break;
		}
		else if (ch == '\b') { // Check for Backspace
			if (!password.empty()) {
				password.pop_back(); // Remove the last character from the password
				cout << "\b \b"; // Erase the last character from the console
			}
		}
		else {
			password.push_back(ch); // Add the character to the password
			cout << '*'; // Display a star
		}
	}

	return password;
}

int Employee::IDcounter = 10000;

#endif // !EMPLOYEE_H