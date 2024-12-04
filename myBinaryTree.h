#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H
#include <iostream>
#include <queue>
#include "Dish.h"

struct MyBinaryTree 
{
    // Definition of a TreeNode
    struct TreeNode 
    {
        Dish data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(Dish value) : data(value), left(nullptr), right(nullptr) {}
    };

    TreeNode* root; // Pointer to the root node

    // Constructor
    MyBinaryTree() : root(nullptr) {}

    //// Destructor
    //~MyBinaryTree() {
    //    clearTree(root);
    //}

    // Insert a value into the tree (Binary Search Tree logic)
    void insert(Dish& value) {
        root = insertNode(root, value);
    }

    //// In-order traversal: Left, Root, Right
    //void inOrderTraversal() const {
    //    inOrder(root);
    //    std::cout << std::endl;
    //}

    //// Pre-order traversal: Root, Left, Right
    //void preOrderTraversal() const {
    //    preOrder(root);
    //    std::cout << std::endl;
    //}

    //// Post-order traversal: Left, Right, Root
    //void postOrderTraversal() const {
    //    postOrder(root);
    //    std::cout << std::endl;
    //}

    // Breadth-first traversal (level-order)
    void levelOrderTraversal() const {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            current->data.printDish();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    // Get the size of the tree (number of nodes)
    int getSize() const {
        return calculateSize(root);
    }

    // Clear the tree
    void clear() {
        clearTree(root);
        root = nullptr;
    }

    Dish* retrieveDishById(int id) {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return nullptr;
        }

        // Use a queue for level-order traversal
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            // Check if the current node's dish ID matches the given ID
            if (current->data.ID == id) {
                return &(current->data);
            }

            // Add the left and right children to the queue if they exist
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        // If no dish with the given ID was found
        std::cout << "Dish with ID " << id << " not found." << std::endl;
        return nullptr;
    }

    void deleteDishById(int id) {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        // Use a queue for level-order traversal
        std::queue<TreeNode*> q;
        q.push(root);

        TreeNode* nodeToDelete = nullptr; // Node to delete
        TreeNode* lastNode = nullptr;    // Last node in level order
        TreeNode* parentOfLastNode = nullptr; // Parent of the last node

        // Perform level-order traversal to find the target node and the last node
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            // Check if the current node is the target node
            if (current->data.ID == id) {
                nodeToDelete = current;
            }

            // Track the last node and its parent
            if (current->left) {
                parentOfLastNode = current;
                q.push(current->left);
            }
            if (current->right) {
                parentOfLastNode = current;
                q.push(current->right);
            }

            lastNode = current;
        }

        // If the node to delete was not found
        if (!nodeToDelete) {
            std::cout << "Dish with ID " << id << " not found." << std::endl;
            return;
        }

        // If the last node is the node to be deleted, simply delete it
        if (nodeToDelete == lastNode) {
            if (parentOfLastNode) {
                if (parentOfLastNode->left == lastNode) parentOfLastNode->left = nullptr;
                else if (parentOfLastNode->right == lastNode) parentOfLastNode->right = nullptr;
            }
            else {
                root = nullptr; // If the tree has only one node
            }
            delete lastNode;
            return;
        }

        // Replace the data of the node to delete with the data of the last node
        nodeToDelete->data = lastNode->data;

        // Remove the last node from the tree
        if (parentOfLastNode) {
            if (parentOfLastNode->left == lastNode) parentOfLastNode->left = nullptr;
            else if (parentOfLastNode->right == lastNode) parentOfLastNode->right = nullptr;
        }
        else {
            root = nullptr; // If the last node was the root
        }
        delete lastNode;

        std::cout << "Dish with ID " << id << " has been deleted." << std::endl;
    }

private:
    // Helper function to insert a node
    TreeNode* insertNode(TreeNode* root, Dish& value) {
        // If the tree is empty, create and return the root node
        if (root == nullptr) {
            return new TreeNode(value);
        }

        // Use a queue to traverse the tree in level-order
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            // Check if the left child is available
            if (current->left == nullptr) {
                current->left = new TreeNode(value);
                return root;
            }
            else {
                q.push(current->left);
            }

            // Check if the right child is available
            if (current->right == nullptr) {
                current->right = new TreeNode(value);
                return root;
            }
            else {
                q.push(current->right);
            }
        }

        return root; // This should never be reached
    }


    //// Helper function for in-order traversal
    //void inOrder(TreeNode* node) const {
    //    if (node == nullptr) return;
    //    inOrder(node->left);
    //    std::cout << node->data << " ";
    //    inOrder(node->right);
    //}

    //// Helper function for pre-order traversal
    //void preOrder(TreeNode* node) const {
    //    if (node == nullptr) return;
    //    std::cout << node->data << " ";
    //    preOrder(node->left);
    //    preOrder(node->right);
    //}

    //// Helper function for post-order traversal
    //void postOrder(TreeNode* node) const {
    //    if (node == nullptr) return;
    //    postOrder(node->left);
    //    postOrder(node->right);
    //    std::cout << node->data << " ";
    //}

    // Helper function to calculate size
    int calculateSize(TreeNode* node) const {
        if (node == nullptr) return 0;
        return 1 + calculateSize(node->left) + calculateSize(node->right);
    }

    // Helper function to clear the tree
    void clearTree(TreeNode* node) {
        if (node == nullptr) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

    // Deletes a dish by ID



};
#endif // !MYBINARYTREE_H

