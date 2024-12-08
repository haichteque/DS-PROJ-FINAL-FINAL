#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include <iostream>
#include "Restaurant.h"

struct MyLinkedList
{
    struct Node
    {
        Restaurant* data;  // Store a pointer to Restaurant
        Node* next;

        Node(Restaurant* value) : data(value), next(nullptr) {}
    };

    Node* head;
    int size;

    MyLinkedList() : head(nullptr), size(0) {}

    ~MyLinkedList()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addFront(Restaurant* value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    void addEnd(Restaurant* value)
    {
        Node* newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        ++size;
    }

    void removeFront()
    {
        if (head == nullptr)
        {
            cout << "List is empty. Nothing to remove." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        --size;
    }

    void removeEnd()
    {
        if (head == nullptr)
        {
            cout << "List is empty. Nothing to remove." << endl;
            return;
        }

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node* temp = head;
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
        --size;
    }

    void removeAtIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Invalid index. No node removed." << endl;
            return;
        }

        if (index == 0)
        {
            removeFront();
            return;
        }

        Node* temp = head;
        for (int i = 0; i < index - 1; ++i)
        {
            temp = temp->next;
        }

        Node* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
        --size;
    }

    Restaurant* retrieveAtIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Invalid index. No node retrieved." << endl;
            return nullptr;
        }

        Node* temp = head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }

        return temp->data;  // Return the pointer directly
    }

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }
};

#endif // !MYLINKEDLIST_H
