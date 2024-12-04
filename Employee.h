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
		bool isSmall = false, isBig = false, isNumber = false, isSpecial = false;

		if (length < 8 || length > 12) {
			return false;  // Return early if length is invalid
		}

		for (char ch : password) {
			if (ch >= 'a' && ch <= 'z') {
				isSmall = true;
			}
			else if (ch >= 'A' && ch <= 'Z') {
				isBig = true;
			}
			else if (ch >= '0' && ch <= '9') {
				isNumber = true;
			}
			else {
				isSpecial = true;  // Anything else is special
			}
		}

		return isSmall && isBig && isNumber && isSpecial;
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