#ifndef REVIEWS_H
#define REVIEWS_H

#include <iostream>
#include"Dish.h"
#include "Customer.h"
#include"Restaurant.h"

using namespace std;


#define capacity 100

class reviewList;
class customer;
class Restaurant;
class Dish;

// Review class
class review
{
public:
    static int IDCounter;
    int ID; // unique ID
    float rating; // 1-5 stars
    string description; // review description
    Customer* reviewer; // reviewer
    Restaurant* restaurant; // restaurant being reviewed
    Dish* dish; // dish being reviewed

    // default constructor
    review() = default;
    // constructor for restaurant review
    review(float rating, string description, Customer* cust, Restaurant* rest = nullptr) : rating(rating), description(description), reviewer(cust), restaurant(rest)
    {
        ID = IDCounter++;
    }
    // constructor for dish review
    review(float rating, string description, Customer* cust, Dish* dish = nullptr) : rating(rating), description(description), reviewer(cust), dish(dish)
    {
        ID = IDCounter++;
    }
    void printDishReview();
    void printRestaurantReview();

    //copy constructor 
    review( review& r)
    {
        this->ID = r.ID;
        rating = r.rating;
        description = r.description;
        reviewer = r.reviewer;
        restaurant = r.restaurant;
        dish = r.dish;
    }

    review* retrieveReviewByID(int revID);

    // display the review

    void displayReview()
    {
        cout << "\nReview ID: " << ID << endl;
        cout << "\nRating: " << rating << " stars" << endl;
        cout << "\nDescription: " << description << endl;
        cout << "\nReviewer: " << reviewer->name << endl;
        if (restaurant)
        {
            printRestaurantReview();
        }
        if (dish)
        {
            printDishReview();
        }
    }

    void editReview()
    {
        int choice;
        do {
            cout << "\nWhat do you want to edit in the review?\n";
            cout << "1. Rating\n";
            cout << "2. Description\n";
            cout << "3. Exit\n";
            cin >> choice;
            if (choice < 1 || choice > 3)
                cout << "\nInvalid choice. Please enter a choice between 1 and 3.\n";
        } while (choice < 1 || choice > 3);
        switch (choice)
        {
        case 1:
        {
            do
            {
                cout << "\nEnter the new rating: ";
                cin >> rating;
                if (rating < 1 || rating > 5)
                    cout << "\nInvalid rating. Please enter a rating between 1 and 5.\n";
            } while (rating < 1 || rating > 5);
            cout << "\nRating updated successfully!\n";
            break;
        }
        case 2:
        {
            cout << "\nEnter the new description: ";
            cin.ignore();
            getline(cin, description);
            cout << "\nDescription updated successfully!\n";
            break;
        }
        case 3:
        {
            cout << "\nExiting review editing...\n";
            break;
        }
        }
    }
};


class MinHeap
{
private:
    review** heapArray;   // Array of reviews
    int heapSize;        // Number of reviews in the heap

    
     // Heapify down for Min-Heap
    void heapifyDown(int i) {
        int smallest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < heapSize && heapArray[leftChild]->rating < heapArray[smallest]->rating)
            smallest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild]->rating < heapArray[smallest]->rating)
            smallest = rightChild;

        if (smallest != i) {
            swap(heapArray[i], heapArray[smallest]);
            heapifyDown(smallest);
        }
    }

    // Heapify up for Min-Heap
    void heapifyUp(int i) {
        while (i != 0 && heapArray[i]->rating < heapArray[(i - 1) / 2]->rating) {
            swap(heapArray[i], heapArray[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

public:
    // Constructor
    MinHeap() {
        heapSize = 0;
        heapArray = new review * [capacity];  // Array of pointers

        // Initialize all pointers to nullptr
        for (int i = 0; i < capacity; i++) {
            heapArray[i] = new review();
        }
    }

    // Insert a review into the Min-Heap
    void insert(review* rev)
    {
        if (heapSize == capacity)
        {
            cout << "Heap overflow, cannot insert review.\n";
            return;
        }
        heapSize++;
        int i = heapSize - 1;
        heapArray[i] = rev;
        heapifyUp(i);
    }

     //Delete the minimum review
    review* deleteMin()
    {
        if (heapSize <= 0)
        {
            cout << "Heap is empty, cannot delete review.\n";
            // Assuming return value for empty heap is handled separately
            return NULL; // Replace with appropriate default constructor
        }
        if (heapSize == 1)
        {
            heapSize--;
            return heapArray[0];
        }
        review* root = heapArray[0];
        heapArray[0] = heapArray[heapSize - 1];
        heapSize--;
        heapifyDown(0);
        return root;
    }

    // Display the heap
    void displayHeap()
    {
        for (int i = 0; i < heapSize; i++)
        {
            cout << heapArray[i]->ID << " " << heapArray[i]->description << endl;
        }
        cout << endl;
    }

    // Display top 5 reviews
    void displayTop5()
    {
        cout << "\nTop 5 reviews:\n";
        for (int i = 0; i < min(5, heapSize); i++)
        {
            if (heapArray[i]->ID > 0)
            heapArray[i]->displayReview();
        }
    }

    // Destructor
    /*~MinHeap()
    {
        for (int i = 0; i < capacity; i++) {
            if (heapArray[i])
            delete heapArray[i];
        }
        delete[] heapArray;
    }*/
};

class MaxHeap {
private:
    review** heapArray;  // Array of pointers to review
    int heapSize;        // Number of reviews in the heap

    // Heapify down for Max-Heap
    void heapifyDown(int i) {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < heapSize && heapArray[leftChild]->rating > heapArray[largest]->rating)
            largest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild]->rating > heapArray[largest]->rating)
            largest = rightChild;

        if (largest != i) {
            swap(heapArray[i], heapArray[largest]);
            heapifyDown(largest);
        }
    }

    // Heapify up for Max-Heap
    void heapifyUp(int i) {
        while (i != 0 && heapArray[i]->rating > heapArray[(i - 1) / 2]->rating) {
            swap(heapArray[i], heapArray[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

public:
    // Constructor
    MaxHeap() {
        heapSize = 0;
        heapArray = new review * [capacity];  // Array of pointers

        // Initialize all pointers to nullptr
        for (int i = 0; i < capacity; i++) {
            heapArray[i] = new review();
        }
    }

    // Insert a review into the Max-Heap
    void insert(review* rev) {
        if (heapSize == capacity) {
            cout << "Heap overflow, cannot insert review.\n";
            return;
        }
        heapArray[heapSize] = rev;  // Store pointer to review
        heapifyUp(heapSize);
        heapSize++;
    }

    // Delete the maximum review
    review* deleteMax() {
        if (heapSize <= 0) {
            cout << "Heap is empty, cannot delete review.\n";
            return nullptr;
        }
        if (heapSize == 1) {
            heapSize--;
            return heapArray[0];  // Return the only element
        }
        review* root = heapArray[0];
        heapArray[0] = heapArray[heapSize - 1];
        heapSize--;
        heapifyDown(0);
        return root;
    }

    // Display the heap
    void displayHeap() {
        for (int i = 0; i < heapSize; i++) {
            heapArray[i]->displayReview();
        }
        cout << endl;
    }

    // Display top 5 reviews
    void displayTop5() {
        cout << "\nTop 5 reviews:\n";
        for (int i = 0; i < min(5, heapSize); i++) {
            if (heapArray[i]->ID > 0)
            heapArray[i]->displayReview();
        }
    }

    // Destructor
    //~MaxHeap() {
    //    for (int i = 0; i < heapSize; i++) {
    //        if (heapArray[i])
    //        delete heapArray[i];  // Free each review
    //    }
    //    delete[] heapArray;  // Free the array of pointers
    //}
};


int review::IDCounter = 10000; // so ID starts with 5 digits

review*  reviewList:: retrieveReviewByID(int revID)
{
    reviewNode* temp = head;

    while (temp != NULL)
    {
        if (temp->rev->ID == revID)
        {
            return temp->rev;
        }
        temp = temp->next;
    }


    return NULL; // Not found
}

void reviewList::displayReviews()
{
    reviewNode* temp = head;
    while (temp != nullptr)
    {
        temp->rev->displayReview();
        cout << endl;
        temp = temp->next;
    }
}
void reviewList::removeReview(int reviewID)
{
    if (head == nullptr)
    {
        cout << "No reviews to remove!" << endl;
        return;
    }

    if (head->rev->ID == reviewID)
    {
        reviewNode* toDelete = head;
        head = head->next;
        delete toDelete->rev;
        delete toDelete;
        cout << "Review with ID " << reviewID << " removed." << endl;
        return;
    }

    reviewNode* temp = head;
    while (temp->next != nullptr && temp->next->rev->ID != reviewID)
    {
        temp = temp->next;
    }

    if (temp->next == nullptr)
    {
        cout << "Review with ID " << reviewID << " not found." << endl;
    }
    else
    {
        reviewNode* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete->rev;
        delete toDelete;
        cout << "Review with ID " << reviewID << " removed." << endl;
    }
}

#endif // !REVIEWS_H
