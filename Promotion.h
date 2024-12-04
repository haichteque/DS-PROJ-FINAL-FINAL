#ifndef PROMOTION_H
#define PROMOTION_H

#include <iostream>
#include <string>
using namespace std;


class Orders;
class Promotion;
class PromotionStack;




// Promotion Class
class Promotion 
{
public:
	static int IDcounter;   // counter for unique ID
    int ID;
    string name;            // Name for the promo 
    float discount;         // Discount percentage (10% = 10)
    int limit;              // Number of times the promotion can be used
    int timesUsed;          // Number of times the promotion has been applied

    // Constructor
    Promotion(string name, float discount, int limit): name(name), discount(discount), limit(limit), timesUsed(0) 
    {
		ID = IDcounter++;
    }

    // Apply promotion to the total order price
    void applyPromotion(float& total) 
    {
        if (timesUsed < limit) 
        {
            total -= (total * (discount / 100));
            timesUsed++;  // Increment the usage count when applied
        }
    }

    // Display Promotion details
    void displayPromotion() const
    {
        cout << "Promotion: " << name << ", Discount: " << discount
            << "%, Remaining Uses: " << (limit - timesUsed) << endl;
    }

    // Check if promotion is still valid (within usage limit)
    bool isValid() const
    {
        return timesUsed < limit;
    }

   
    void markAsExpired()
    {
        if (timesUsed >= limit) 
        {
            cout << "Promotion " << name << " has expired!" << endl;
        }
    }
};
// stack node
struct PromotionNode 
{
    Promotion* promo;        //data
    PromotionNode* next;     // Pointer to the next node in the stack
};

// stack to handle promotions
class PromotionStack
{
public:
    PromotionNode* top; 

    // Constructor
    PromotionStack() : top(nullptr) {}

    // Push a new promotion onto the stack
    void push(Promotion* promo)
    {
        PromotionNode* newNode = new PromotionNode();
        newNode->promo = promo;
        newNode->next = top;
        top = newNode;
    }

    // Pop the top promotion from the stack
    Promotion* pop()
    {
        if (top == nullptr)
        {
            cout << "\nNo promotion to remove!" << endl;
            return nullptr;
        }
        PromotionNode* temp = top;
        Promotion* poppedPromo = temp->promo;
        top = top->next;
        delete temp;
        return poppedPromo;
    }

    // Peek 
    Promotion* peek() 
    {
        if (top == nullptr) 
        {
            return nullptr;
        }
        return top->promo;
    }

    bool isEmpty() const 
    {
        return top == nullptr;
    }

    void displayStack() const 
    {
        PromotionNode* current = top;
        while (current != nullptr) 
        {
            current->promo->displayPromotion();
            current = current->next;
        }
    }
};


int Promotion::IDcounter = 1000; // Start with 4-digit IDs

#endif //PROMOTION_H