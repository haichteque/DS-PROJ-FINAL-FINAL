#pragma once
#include "Employee.h"
#include "Customer.h"
#define HASHSIZE 100 // The size of the hashmap
class HashMap {
public:
	// variables
	int baseID; // The ID that we will use to minus from the ID to access the array
	Employee* employee[HASHSIZE];
	Customer* customer[HASHSIZE];

	HashMap() {
		baseID = 10000; // Since we're starting with 5 digits
		for (int i = 0; i < HASHSIZE; i++) {
			employee[i] = NULL;
			customer[i] = NULL;
		}


	}

	// Insert an employee into the hashmap
	void insertEmployee(Employee& e) {
		int index = e.ID - baseID;
		employee[index] = &e;
	}

	void insertEmployee(Employee* e) { // Overloaded
		int index = e->ID - baseID;
		employee[index] = e;
	}

	// Retrieve an employee from the hashmap
	Employee* retrieveEmployee(int ID) {
		int index = ID - baseID;
		return employee[index];
	}

	// Checks if an email already exists or not for employee 
	bool isEmailTaken(Employee* e) {
		string email = e->email;

		for (int i = 0; i < HASHSIZE; i++) {
			if (employee[i]) {
				if (employee[i]->email == email) return true;
			}
		}

		return false;

	}

	// Checks if an emial already exists or not for customer
	bool isCustomerEmailTaken(Customer* c) {
		string email = c->email;

		for (int i = 0; i < HASHSIZE; i++) {
			if (customer[i]) {
				if (customer[i]->email == email) return true;
			}
		}

		return false;
	}

	// Insert a customer into its hashmap
	void insertCustomer(Customer* c) {
		int index = c->ID - baseID;
		customer[index] = c;
	}

	// Retrieve a customer from the hashmap
	Customer* retrieveCustomer(int ID) {
		int index = ID - baseID;
		return customer[index];
	}

};