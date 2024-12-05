#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "RestaurantHub.h"
#include "Employee.h"
#include "Orders.h"
#include "Reviews.h"
using namespace std;

class Orders;
class OrderNode;
class OrdersList;
class Customer;
class Employee;
class RestaurantHub;
class review;


class reviewNode
{
public:
	review * rev; // Pointer to the Review object
	reviewNode* next;     // Pointer to the next node

	// Constructor
	reviewNode(review* review)
	{
		this->rev = review;
		this->next = nullptr;
	}
};

class reviewList
{
private:
	reviewNode* head; // Pointer to the head of the list

public:
	// Constructor
	reviewList() : head(nullptr) {}

	// Add a review to the linked list
	void addReview(review* review)
	{
		reviewNode* newNode = new reviewNode(review);
		if (head == nullptr)
		{
			head = newNode;
		}
		else
		{
			reviewNode* temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	// Retrieve a review by its ID
	review* retrieveReviewByID(int revID);
	


	// Display all reviews in the linked list
	void displayReviews();
	

	// Remove a review by ID
	void removeReview(int reviewID);
	
	


};


class OrderNode
{
public:
	Orders * order;       // Pointer to the order object

	OrderNode* next;   // Pointer to the next node in the list

	

	OrderNode(Orders* order, OrderNode* next) :order(order), next(next) {}
};

class OrdersList // order linked list for orders
{
public:
	OrderNode* head;

	// Constructor
	OrdersList() : head(nullptr) {}

	

	// insert a order into the list
	void addOrders(Orders* order)
	{
		OrderNode* newNode = new OrderNode(order, NULL);
		if (!head)
		{
			head = newNode;
		}
		else
		{
			OrderNode* current = head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = newNode;
		}
	}

	int getTotalOrders() {
		OrderNode* temp = head;
		int count = 0;
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}
		return count;
	}
	void print()
	{
		OrderNode* current = head;
		while (current != nullptr)
		{
			current->order->displayOrder();
			current = current->next;
		}
	}
};



class Customer 
{
public:
	// variables
	string name;
	string email;
	string password;
	static int IDcounter;
	int ID;
	OrdersList orderHistory;
	Orders * currentOD;
	reviewList reviewHistory;

	Customer() = default;
	Customer(string name, string email, string password) {
		this->name = name;
		this->password = password;
		this->email = email;
		orderHistory = OrdersList();
	}

	// A function that lets you edit your account details
	void EditAccountDetails() 
	{
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

			} while (!Employee::isPasswordValid(password));
		}
	}

};

void Orders::displayOrder()
{
	cout << "\nOrder ID: " << ID << endl;
	cout << "Restaurant: " << restaurantName << endl;
	if (customer)
		cout << "Customer: " << customer->name << endl;
	if (waiter)
		cout << "Waiter: " << waiter->name << endl;
	cout << "Order Type: " << type << endl;
	if (promotion != nullptr)
	{
		cout << "Promotion Applied: " << promotion->name << " - " << promotion->discount << "% Discount" << endl;
	}
	cout << "Ordered Dishes: " << endl;
	orderedDishes.displayDishes();
	cout << "Total: Rs. " << total << endl;
}

int Customer::IDcounter = 10000;

#endif // !CUSTOMER_H
