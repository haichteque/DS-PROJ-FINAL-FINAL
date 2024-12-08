#pragma once
#include <iostream>
#include <string>
#include "Menu.h"
#include "Employee.h"
#include "ordersPriorQueue.h"
#include "Orders.h"
#include "Reviews.h"
using namespace std;

class Restaurant;
class Employee;
class MaxHeap;
class MinHeap;
class Reviews;


class Restaurant
{
public:
	static int IDcount; // A counter of the restaurant IDs
	int ID;
	string name;
	string type;
	Menu menu;
	Employee* manager;
	string location; // Location of the restaurant
	orderPriorQ orderQueue; // Queue for orders that have not been processed
	orderPriorQ processedOrders; // Queue for orders that have been processed, and need to be delivered
	MaxHeap posReviews; // Max heap for positive reviews
	MinHeap negReviews; // Min heap for negative reviews

	Restaurant() = default;

	// Parameterized constructor 1
	Restaurant(string name, string type, Menu menu) { // ID will only be incremented when a parameterized constructor is used
		this->name = name;
		this->type = type;
		this->menu = menu;
		this->ID = IDcount++;
		orderQueue = orderPriorQ();

	}

	// Parameterized constructor 2
	Restaurant(string name, string type) { // ID will only be incremented when a parameterized constructor is used
		this->name = name;
		this->type = type;
		this->ID = IDcount++;
		orderQueue = orderPriorQ();

	}

	// Print the restaurant's details
	void printRestaurant()
	{
		cout << "ID: " << ID << " Restaurant name: " << name << " Type: " << type << " Manager: " << manager->name << endl << " Location: " << location << endl;
	}


};
void review:: printRestaurantReview()
{
	cout << restaurant->name << endl;
}


int Restaurant::IDcount = 10000; // so ID starts with 5 digits
