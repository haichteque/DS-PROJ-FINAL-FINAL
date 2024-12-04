#pragma once
#include <iostream>
#include <string>
#include "MyBinaryTree.h"
using namespace std;

class Menu {
public:
	// variables
	static int IDcount;
	int ID;
	string* name; // Name of the restaurant that the menu is assigned to
	int totalDishes;
	MyBinaryTree dishes;


	Menu() {
		totalDishes = 0;
		ID = IDcount++;
	}

	Menu(string* name, int totalDishes) {
		this->name = name;
		this->totalDishes = totalDishes;
		ID = IDcount++;
	}

	// FUNCTIONS

	// A function to initalize the menu
	void initializeMenu() {
		bool flag = true; // True if want to add dishes
		do {
			// Initialize a dish then add
			Dish temp;
			cout << "Enter the name of the dish that you wish to add: ";
			//cin.ignore();
			getline(cin, temp.name);
			cout << "Enter the type of the dish (appetizers,burgers,pizzas etc): ";
			getline(cin, temp.type);
			cout << "Enter the price of the dish: ";
			do {
				cin >> temp.price;
			} while (temp.price < 0);

			temp.ID = temp.IDcount++;

			// Add the dish to the menu, and increase totaldishes count
			dishes.insert(temp);
			totalDishes++;

			// Ask if want to add more dishes
			cout << "Do you want to add more dishes? (y/n): ";
			char dishchoice;
			cin >> dishchoice;
			if (dishchoice == 'y') {

			}
			else {
				flag = false;
			}

		} while (flag);

		//cout << "Menu successfully initialized" << endl;

	}

	// A function to print the menu
	void printMenu() {
		dishes.levelOrderTraversal();
	}

	// A function to edit a dish
	void editDish(int dishID) {
		Dish* d = dishes.retrieveDishById(dishID);
		if (d) { // If the dish exists
			cout << liner;
			cout << "What would you like to change about the dish: " << endl;
			cout << "1. Name" << endl;
			cout << "2. Type" << endl;
			cout << "3. Price" << endl;
			int editChoice;
			do {
				cin >> editChoice;
			} while (editChoice < 1 || editChoice > 3);
			cin.ignore();
			switch (editChoice) {
			case 1: {
				cout << "Enter the new name of the dish: ";
				getline(cin, d->name);

				break;
			}
			case 2: {
				cout << "Enter the new type of the dish (e.g pizza, burger, shawarma): ";
				getline(cin, d->type);
				break;
			}

			case 3: {
				cout << "Enter the new price of the dish: ";
				cin >> d->price;
				break;
			}


			} // Switch ender
			cout << "Dish successfully edited!" << endl;
		}
		else {
			cout << "Sorry, the ID is invalid or the dish does not exist!" << endl;
		}
	}

};

int Menu::IDcount = 10000;