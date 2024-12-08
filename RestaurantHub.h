#pragma once
#include "Restaurant.h"
#include "Menu.h"
#include "Dish.h"
#include "myLinkedList.h"
#include "Employee.h"
#include "HashMap.h"
#include "Customer.h"
#include "Orders.h"
#include <conio.h>
#include "Graph.h"



class RestaurantHub {
public:
    // Variables
    MyLinkedList restaurants;  // Stores pointers to Restaurant objects
    HashMap hash;

    // FUNCTIONS

    // A function to add a restaurant (stores pointer)
    void addRestaurant(Restaurant* r) {
        restaurants.addEnd(r);  // Add pointer to the linked list
        cout << "Restaurant added successfully!" << endl;
    }

    // A function to initialize a restaurant
    void initializeRestaurant(Graph& graph) {
        Restaurant* r = new Restaurant;  // Dynamically allocate new restaurant
        cout << "Enter the name of the restaurant that you wish to add: ";
        cin.ignore();
        getline(cin, r->name);
        cout << "Enter the type of the restaurant (Fast Food, Cake, Bakery, Chinese, etc): ";
        getline(cin, r->type);

        // Set the location of the restaurant
        graph.printVertices();
        cout << liner;
        cout << "Enter the location of the restaurant: ";
        getline(cin, r->location);



        // Assign ID to restaurant
        r->ID = r->IDcount++;

        // Initialize the restaurant's menu
        r->menu.initializeMenu();
        r->menu.name = &r->name;  // Assign restaurant name to menu

        // Add manager to restaurant
        r->manager = hash.retrieveEmployee(initializeEmployee(*r));

        // Add restaurant to the list of restaurants
        addRestaurant(r);  // Use the fixed addRestaurant function
    }

    // A function to print all restaurants
    void printRestaurants() {
        MyLinkedList::Node* temp = restaurants.head;
        while (temp != nullptr) {
            temp->data->printRestaurant();  // Print via pointer
            temp = temp->next;
        }
    }

    // A function to remove a restaurant
    void removeRestaurant(int index) {
        Restaurant* temp = restaurants.retrieveAtIndex(index);
        for (int i = 0; i < HASHSIZE; i++) {
            if (hash.employee[i] && hash.employee[i]->workplace == temp) {
                
                hash.employee[i]->workplace = NULL;
            }
        }
        restaurants.removeAtIndex(index);
    }

    // A function to edit a restaurant
    void editRestaurant(int index) {
        cout << "===============" << endl;
        // Retrieve the restaurant first
        Restaurant* r = restaurants.retrieveAtIndex(index);

        if (!r) {
            cout << "Invalid restaurant ID." << endl;
            return;
        }

        // Menu to edit restaurant details or menu details
        cout << "Welcome! What would you like to edit?" << endl;
        cout << "1. Restaurant details (name of restaurant, type, etc)" << endl;
        cout << "2. Menu details" << endl;
        cout << "Enter your choice: ";
        int rchoice;
        cin >> rchoice;

        switch (rchoice) {
        case 1: {
            cout << "What would you like to change about the restaurant?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Type" << endl;
            cout << "Enter your choice: ";
            int resChoice;
            cin >> resChoice;

            string changer;
            if (resChoice == 1) {
                cout << "Enter the new name of the restaurant: ";
                cin.ignore();
                getline(cin, changer);
                r->name = changer;
            }
            else if (resChoice == 2) {
                cout << "Enter the new type of the restaurant: ";
                cin.ignore();
                getline(cin, changer);
                r->type = changer;
            }
            cout << "Changes successfully made!" << endl;
            break;
        }
        case 2: {
            r->menu.printMenu();
            cout << "Enter the ID of the item that you wish to change: ";
            int itemID;
            cin >> itemID;
            Dish* d = r->menu.dishes.retrieveDishById(itemID);
            if (!d) {
                cout << "Dish not found!" << endl;
                break;
            }
            cout << "What would you like to change about this dish?" << endl;
            cout << "1. Name" << endl;
            cout << "2. Type" << endl;
            cout << "3. Price" << endl;
            cout << "Enter your choice: ";
            int dishChoice;
            cin >> dishChoice;

            string changer;
            double price;
            if (dishChoice == 1) {
                cout << "Enter the new name of the dish: ";
                cin.ignore();
                getline(cin, changer);
                d->name = changer;
            }
            else if (dishChoice == 2) {
                cout << "Enter the new type of the dish: ";
                cin.ignore();
                getline(cin, changer);
                d->type = changer;
            }
            else if (dishChoice == 3) {
                cout << "Enter the new price of the dish: ";
                cin >> price;
                d->price = price;
            }
            cout << "Changes made successfully!" << endl;
            break;
        }
        }
    }

    int initializeEmployee(Restaurant& r) {
        Employee* e = new Employee;
        cout << "Enter the employee's name: ";
        cin.ignore();
        getline(cin, e->name);
        cout << "Enter the employee's email: ";
        cin >> e->email;
        while (hash.isEmailTaken(e)) {
            cout << "invalid email, enter again: ";
            cin >> e->email;
        }
        cout << "Enter the employee's password: ";
        cin >> e->password;
        while (!e->isPasswordValid(e->password)) {
            cout << "Enter a valid password: ";
            cin >> e->password;
        }
        e->workplace = &r; // Where the employee works at

        cout << "Is employee manager(y/n): ";
        char ch;
        cin >> ch;
        while (ch != 'y' && ch != 'n') {
            cin >> ch;
        }
        if (ch == 'y') {
            e->type = 1; // Manager

        }
        else {
            e->type = 0; // Not Manager
        }


        // Add employee to the hashmap
        e->ID = e->IDcounter++;
        hash.insertEmployee(e);
        return e->ID;
    }

    // A function to authenticate the employee, returns ID of the employee
    int authenticatedEmployee() {
        string email, password;
        cout << "Enter your username/email: ";
        cin >> email;

        password = getPassword();
        bool exists = 0;
        for (int i = 0; i < HASHSIZE; i++) {
            if (hash.employee[i]) { // If employee exists
                if ((hash.employee[i]->email == email || hash.employee[i]->name == email) && hash.employee[i]->password == password) {
                    exists = true;
                    return hash.employee[i]->ID;

                }
            }
        }

        return 0;


    }

    // A function to authenticate the customer, returns ID of the customer
    int authenticatedCustomer()
    {
        string email, password;
        cout << "Enter your username/email: ";
        cin >> email;

        password = getPassword();
        cout << "Confirm your password: ";
        string confirmpassword = getPassword();
        bool exists = 0;
        for (int i = 0; i < HASHSIZE; i++) {
            if (hash.customer[i]) { // If customer exists
                if ((hash.customer[i]->email == email || hash.customer[i]->name == email) && hash.customer[i]->password == password && confirmpassword == password) {
                    exists = true;
                    return hash.customer[i]->ID;

                }
            }
        }

        return 0;
    }


    // A function to initialize employee which is not manager, but now it will initialize Driver as well
    int initializeEmployeeNotManager(Restaurant& r) {
        Employee* e = new Employee;
        cout << "Enter the employee's name: ";
        cin.ignore();
        getline(cin, e->name);
        cout << "Enter the employee's email: ";
        cin >> e->email;
        while (hash.isEmailTaken(e)) {
            cout << "invalid email, enter again: ";
            cin >> e->email;
        }
        cout << "Enter the employee's password: ";
        cin >> e->password;
        while (!e->isPasswordValid(e->password)) {
            cout << "Enter a valid password: ";
            cin >> e->password;
        }
        e->workplace = &r; // Where the employee works at

        cout << "Are you a regular employee or a driver" << endl;
        cout << "1. Employee" << endl;
        cout << "2. Driver" << endl;
        int typeChoice;
        do {
            cin >> typeChoice;
        } while (typeChoice < 1 || typeChoice > 2);
        e->type = typeChoice; // Sets the driver


        // Add employee to the hashmap
        e->ID = e->IDcounter++;
        hash.insertEmployee(e);
        return e->ID;
    }

    // A function to register as a Customer
    void registerCustomer() {
        Customer* customer = new Customer;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, customer->name);
        cout << "Enter your email: ";
        do {
            getline(cin, customer->email);
        } while (hash.isCustomerEmailTaken(customer)); // Email validation
        cout << "Email valid!" << endl;
        cout << "Enter your password: ";
        do {
            cin >> customer->password;
            if (!Employee::isPasswordValid(customer->password)) cout << "Password not valid!" << endl;
        } while (!Employee::isPasswordValid(customer->password)); // Password validation
        cout << "Password valid!" << endl;

        // Assign ID and add to hashmap
        customer->ID = customer->IDcounter++;
        hash.insertCustomer(customer);

        cout << "Customer successfully registered!" << endl;

    }
};