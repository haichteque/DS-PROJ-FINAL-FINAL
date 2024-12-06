#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H
#include <iostream>
#include "Dish.h"






struct MyBinaryTree 
{
    
    struct TreeNode 
    {
        Dish data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(Dish value) : data(value), left(nullptr), right(nullptr) {}
    };


    struct Node {
        TreeNode* data;
        Node* next;
        Node(TreeNode* val) : data(val), next(nullptr) {}
    };

    class LinkedListQueue {
    public:
        Node* front;
        Node* rear;
        LinkedListQueue() : front(nullptr), rear(nullptr) {}

        bool is_empty() {
            return front == nullptr;
        }

        void enqueue(TreeNode* val) {
            Node* newNode = new Node(val);
            if (is_empty()) {
                front = rear = newNode;
            }
            else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        TreeNode* dequeue() {
            if (is_empty()) {
                throw runtime_error("Queue  empty");
            }
            Node* temp = front;
            TreeNode* data = temp->data;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            return data;
        }

        

        

        int size() {
            int count = 0;
            Node* temp = front;
            while (temp != nullptr) {
                count++;
                temp = temp->next;
            }
            return count;
        }
    };

    TreeNode* root; 

    // Constructor
    MyBinaryTree() : root(nullptr) {}

    

   
    void insert(Dish& value) {
        root = insertNode(root, value);
    }

    
    void levelOrderTraversal() const {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }
        LinkedListQueue q;
        q.enqueue(root);
        while (!q.is_empty()) {
            TreeNode* current = q.dequeue();
            current->data.printDish();
            if (current->left) q.enqueue (current->left);
            if (current->right) q.enqueue(current->right);
        }
        std::cout << std::endl;
    }

    
    int getSize() const {
        return calculateSize(root);
    }

   
   

    Dish* retrieveDishById(int id) {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return nullptr;
        }

        
        LinkedListQueue q;
        q.enqueue(root);

        while (!q.is_empty()) {
            TreeNode* current = q.dequeue();
            

            
            if (current->data.ID == id) {
                return &(current->data);
            }

            
            if (current->left) q.enqueue(current->left);
            if (current->right) q.enqueue(current->right);
        }

        
        std::cout << "Dish with ID " << id << " not found." << std::endl;
        return nullptr;
    }

    void deleteDishById(int id) {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        
        LinkedListQueue q;
        q.enqueue(root);

        TreeNode* nodeToDelete = nullptr; 
        TreeNode* lastNode = nullptr;    
        TreeNode* parentOfLastNode = nullptr; 

        
        while (!q.is_empty()) {
            TreeNode* current = q.dequeue();
            

            
            if (current->data.ID == id) {
                nodeToDelete = current;
            }

            
            if (current->left) {
                parentOfLastNode = current;
                q.enqueue(current->left);
            }
            if (current->right) {
                parentOfLastNode = current;
                q.enqueue(current->right);
            }

            lastNode = current;
        }

        
        if (!nodeToDelete) {
            std::cout << "Dish with ID " << id << " not found." << std::endl;
            return;
        }

        
        if (nodeToDelete == lastNode) {
            if (parentOfLastNode) {
                if (parentOfLastNode->left == lastNode) parentOfLastNode->left = nullptr;
                else if (parentOfLastNode->right == lastNode) parentOfLastNode->right = nullptr;
            }
            else {
                root = nullptr; 
            }
            delete lastNode;
            return;
        }

        
        nodeToDelete->data = lastNode->data;

        
        if (parentOfLastNode) {
            if (parentOfLastNode->left == lastNode) parentOfLastNode->left = nullptr;
            else if (parentOfLastNode->right == lastNode) parentOfLastNode->right = nullptr;
        }
        else {
            root = nullptr; 
        }
        delete lastNode;

        std::cout << "Dish with ID " << id << " has been deleted." << std::endl;
    }

private:
   
    TreeNode* insertNode(TreeNode* root, Dish& value) {
       
        if (root == nullptr) {
            return new TreeNode(value);
        }

       
        LinkedListQueue q;
        q.enqueue(root);

        while (!q.is_empty()) {
            TreeNode* current = q.dequeue();
            

           
            if (current->left == nullptr) {
                current->left = new TreeNode(value);
                return root;
            }
            else {
                q.enqueue(current->left);
            }

            
            if (current->right == nullptr) {
                current->right = new TreeNode(value);
                return root;
            }
            else {
                q.enqueue(current->right);
            }
        }

        return root; // This should never be reached
    }


   
    int calculateSize(TreeNode* node) const {
        if (node == nullptr) return 0;
        return 1 + calculateSize(node->left) + calculateSize(node->right);
    }

   



};
#endif // !MYBINARYTREE_H

