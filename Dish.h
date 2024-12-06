#ifndef DISH_H
#define DISH_H



#include <iostream>
#include <string>
#include "Reviews.h"
using namespace std;

class review;
class MaxHeap;
class MinHeap;


class Dish {
public:
	// variables
	static int IDcount;
	int ID;
	string name; // Name of the dish
	string type;
	double price;
	MaxHeap posReviews;
	MinHeap negReviews;


	Dish() = default;
	Dish(string name, string type, double price) 
	{
		ID = IDcount++;
		this->name = name;
		this->type = type;
		this->price = price;

	}

	// FUNCTIONS

	

	// A function to print the dish
	void printDish() {
		cout << "DISH ID: " << ID << " Name: " << name << " Type: " << type << "Price: " << price << endl;
	}




};

int Dish::IDcount = 10000;

float DishList::calculateTotalPrice()
{
	float total = 0;
	DishNode* current = head;
	while (current != nullptr)
	{
		total += current->dish->price * current->quantity;
		current = current->next;
	}
	return total;
}
void DishList:: displayDishes()
{
	DishNode* current = head;
	while (current != nullptr)
	{
		
			cout << "Dish: " << current->dish->name
				<< "\nQuantity: " << current->quantity
				<< "\nPrice per unit: Rs. " << current->dish->price

				<< endl;
		
		
			current = current->next;
	}
}
void DishList:: removeDish(int id, int quantity)
{
	DishNode* current = head;
	DishNode* prev = nullptr;
	while (current != nullptr)
	{
		if (current->dish->ID == id)
		{
			if (current->quantity > quantity)
			{
				current->quantity -= quantity;
				return;
			}
			else
			{
				if (prev)
				{
					prev->next = current->next;
				}
				else
				{
					head = current->next;
				}
				DishNode* temp = current;
				current = current->next;
				delete temp;
				return;
			}
		}
		prev = current;
		current = current->next;
	}
	cout << "\nDish with ID " << id << " not found in the order." << endl;
}
void review::printDishReview()
{
	cout << "Dish: " << dish->name << endl;

}

float DishList:: getCost() {
	if (head) {
		DishNode* temp = head;
		float cost = 0;
		while (temp != NULL) {
			cost += temp->quantity * temp->dish->price;
			temp = temp->next;
		}

		return cost;
	}

}
bool DishList:: removedDish()
{
	if (head == nullptr)
		return true;
	DishNode* current = head;
	while (current != nullptr)
	{
		if (current->dish->ID < 0)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}


#endif // !DISH_H

