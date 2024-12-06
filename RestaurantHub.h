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



class RestaurantHub {
public:
    // Variables
    MyLinkedList restaurants;  // Stores pointers to Restaurant objects
    HashMap hash;

    // FUNCTIONS

    // A function to add a restaurant (stores pointer)
    void addRestaurant(Restaurant* r) {
        restaurants.addEnd(r);  // Add pointer to the linked list
        std::cout << "Restaurant added successfully!" << std::endl;
    }

    // A function to initialize a restaurant
    void initializeRestaurant() {
        Restaurant* r = new Restaurant;  // Dynamically allocate new restaurant
        std::cout << "Enter the name of the restaurant that you wish to add: ";
        std::cin.ignore();
        getline(std::cin, r->name);
        std::cout << "Enter the type of the restaurant (Fast Food, Cake, Bakery, Chinese, etc): ";
        getline(std::cin, r->type);

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
        std::cout << "===============" << std::endl;
        // Retrieve the restaurant first
        Restaurant* r = restaurants.retrieveAtIndex(index);

        if (!r) {
            std::cout << "Invalid restaurant ID." << std::endl;
            return;
        }

        // Menu to edit restaurant details or menu details
        std::cout << "Welcome! What would you like to edit?" << std::endl;
        std::cout << "1. Restaurant details (name of restaurant, type, etc)" << std::endl;
        std::cout << "2. Menu details" << std::endl;
        std::cout << "Enter your choice: ";
        int rchoice;
        std::cin >> rchoice;

        switch (rchoice) {
        case 1: {
            std::cout << "What would you like to change about the restaurant?" << std::endl;
            std::cout << "1. Name" << std::endl;
            std::cout << "2. Type" << std::endl;
            std::cout << "Enter your choice: ";
            int resChoice;
            std::cin >> resChoice;

            std::string changer;
            if (resChoice == 1) {
                std::cout << "Enter the new name of the restaurant: ";
                std::cin.ignore();
                getline(std::cin, changer);
                r->name = changer;
            }
            else if (resChoice == 2) {
                std::cout << "Enter the new type of the restaurant: ";
                std::cin.ignore();
                getline(std::cin, changer);
                r->type = changer;
            }
            std::cout << "Changes successfully made!" << std::endl;
            break;
        }
        case 2: {
            r->menu.printMenu();
            std::cout << "Enter the ID of the item that you wish to change: ";
            int itemID;
            std::cin >> itemID;
            Dish* d = r->menu.dishes.retrieveDishById(itemID);
            if (!d) {
                std::cout << "Dish not found!" << std::endl;
                break;
            }
            std::cout << "What would you like to change about this dish?" << std::endl;
            std::cout << "1. Name" << std::endl;
            std::cout << "2. Type" << std::endl;
            std::cout << "3. Price" << std::endl;
            std::cout << "Enter your choice: ";
            int dishChoice;
            std::cin >> dishChoice;

            std::string changer;
            double price;
            if (dishChoice == 1) {
                std::cout << "Enter the new name of the dish: ";
                std::cin.ignore();
                getline(std::cin, changer);
                d->name = changer;
            }
            else if (dishChoice == 2) {
                std::cout << "Enter the new type of the dish: ";
                std::cin.ignore();
                getline(std::cin, changer);
                d->type = changer;
            }
            else if (dishChoice == 3) {
                std::cout << "Enter the new price of the dish: ";
                std::cin >> price;
                d->price = price;
            }
            std::cout << "Changes made successfully!" << std::endl;
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


    // A function to initialize employee which is not manager
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

        e->type = 0;


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