#ifndef ORDERS_H
#define ORDERS_H


#include<string>
#include "Dish.h"
#include "Employee.h"
#include "Customer.h"
#include "Promotion.h"

class OrdersList;
class Orders;
class Dish;
class Customer;
class Promotion;

class DishNode
{
public:
	Dish* dish;       // Pointer to the dish object
	int quantity;     // Quantity of the dish ordered
	DishNode* next;   // Pointer to the next node in the list

	DishNode(Dish* dish, int quantity) : dish(dish), quantity(quantity), next(nullptr) {}
};

class DishList // dish linked list for orders
{
public:
    DishNode* head;

    // Constructor
    DishList() : head(nullptr) {}

    // Destructor to clean up dynamically allocated memory

	// insert a dish into the list
    void addDish(Dish* dish, int quantity)
    {
        DishNode* newNode = new DishNode(dish, quantity);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            DishNode* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }
	//Display all the dishes in the list
    void displayDishes();
    
	//calculate the total price of all the dishes in the list
    float calculateTotalPrice();
	//remove a dish from the list based on the dish ID based on quantity
    void removeDish(int id, int quantity);
    

};


class Orders
{
public:
    static int IDcounter;                   // counter for unique ID
    int ID;                                 // unique ID
    DishList orderedDishes;                 // list of dishes
    float total;                            // total cash
    Employee* waiter;                       // who took the order
    Customer* customer;                     // who placed the order
    string type;                            // order type (premium, express, or normal)
    float priority;                         // priority of the order
    Promotion* promotion;                   // promotion applied (if any)
	string restaurantName;                  // name of the restaurant

    // Constructor
    Orders(DishList orders, Customer* cust, string type,string restName)
		: orderedDishes(orders), total(0), waiter(NULL), customer(cust), type(type), promotion(nullptr), restaurantName(restName)
    {
        ID = IDcounter++;
        setPriority(type);
    }

    // Set the order priority based on type
    void setPriority(string type)
    {
        if (type == "premium" || type == "Premium")
        {
            priority = 1;
        }
        else if (type == "express" || type == "Express")
        {
            priority = 2;
        }
        else
        {
            priority = 3;
        }
    }

    // Set the waiter for the order
    void setWaiter(Employee* waiter)
    {

        this->waiter = waiter;
    }

    // Set the total of the order
    void setTotal(float total)
    {
        this->total = total;
    }

    // Calculate the total price of the order
    void calculateTotal()
    {
        total = orderedDishes.calculateTotalPrice();
    }
    float getProcessingCost()
    {
        if (type == "Premium" || type == "Premium")
            return 500.0;
		else if (type == "Express" || type == "Express")
			// 10% of the total price
			return (total * 0.1);
		else
			return 0;
    }

    // Remove a dish from the order
    void removeDish(int id, int quantity)
    {
        orderedDishes.removeDish(id, quantity);
        calculateTotal();  // Recalculate total after removing a dish
    }
	void addPromotion(Promotion* promo)
	{
		promotion = promo;
	}
    // Display the order details
    void displayOrder();
    
};



void applyOrderPromotion(PromotionStack& promoStack, Orders& order)
{
    if (!promoStack.isEmpty())
    {
        // Apply the top promotion 
        Promotion* currentPromo = promoStack.peek();
        if (currentPromo->isValid())
        {
            currentPromo->applyPromotion(order.total);
            cout << "\nApplied Promotion: ";
            currentPromo->displayPromotion();
            order.addPromotion(currentPromo);
        }
        else
        {
            //invalid promo meaning used limit amount of times
            cout << "\nPromotion " << currentPromo->name << " is expired. Popping it from the stack." << endl;
            promoStack.pop();
            applyOrderPromotion(promoStack, order);  // Try applying the next valid promotion
        }
    }
    else
    {
        cout << "\nNo promotion applied.No Promos found!" << endl;
    }
}

int Orders::IDcounter = 10000;
#endif // !ORDERS_H
