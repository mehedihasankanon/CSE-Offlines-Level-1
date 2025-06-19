#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here

    bool inserthelp(Node *node, Key key, Value value)
    {
        if (key == node->key)
        {
            return false;
        }

        if (key < node->key)
        {
            if (node->left)
            {
                return inserthelp(node->left, key, value);
            }
            node->left = new Node(key, value);
            node_count++;
            return true;
        }
        else
        {
            if (node->right)
            {
                return inserthelp(node->right, key, value);
            }
            node_count++;
            node->right = new Node(key, value);
            return true;
        }
    }

    Node *removehelp(Node *node, Key key)
    {
        if (!node)
            return nullptr;

        if (key < node->key)
        {
            node->left = removehelp(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = removehelp(node->right, key);
        }
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }

            if (!node->right)
            {
                Node *ret = node->left;
                delete node;
                return ret;
            }
            else if (!node->left)
            {
                Node *ret = node->right;
                delete node;
                return ret;
            }

            Node *successor = node->right;
            while (successor->left)
            {
                successor = successor->left;
            }

            node->key = successor->key;
            node->value = successor->value;
            node->right = removehelp(node->right, node->key);
        }

        return node;
    }

    bool findhelp(Node *node, Key key) const
    {
        if (!node)
            return false;

        if (node->key == key)
            return true;
        if (key < node->key)
            return findhelp(node->left, key);
        return findhelp(node->right, key);
    }

    Value gethelp(Node *node, Key key) const
    {
        if (node->key == key)
            return node->value;

        if (key < node->key)
            return gethelp(node->left, key);
        return gethelp(node->right, key);
    }

    void updatehelp(Node *node, Key key, Value value)
    {
        if (node->key == key)
        {
            node->value = value;
            return;
        }

        if (key < node->key)
        {
            updatehelp(node->left, key, value);
            return;
        }
        updatehelp(node->right, key, value);
    }

    void clearhelp(Node *node)
    {
        if (!node)
            return;

        clearhelp(node->left);
        clearhelp(node->right);
        delete node;
    }

    // size_t sizehelp(Node *node) const
    // {
    //     if (!node)
    //         return 0;

    //     return sizehelp(node->left) + 1 + sizehelp(node->right);
    // }

    Key find_minhelp(Node *node) const
    {
        if (!node->left)
            return node->key;
        return find_minhelp(node->left);
    }

    Key find_maxhelp(Node *node) const
    {
        if (!node->right)
            return node->key;
        return find_maxhelp(node->right);
    }

    // std::string to_string(Node *node)
    // {
    //     if (!node)
    //         return "()";
    //     return to_string(node->key) + "," + to_string(node->value);
    // }

    void print_default(Node *node) const
    {
        if (!node)
        {
            std::cout << "()";
            return;
        }

        std::cout << "(" << node->key << ":" << node->value;
        if (node->right)
        {
            std::cout << " ";
            print_default(node->left);
            std::cout << " ";
            print_default(node->right);
        }
        else if (node->left)
        {
            std::cout << " ";
            print_default(node->left);
        }
        std::cout << ")";
    }

    void print_inorder(Node *node) const
    {
        if (node == root && !root)
        {
            std::cout << "()";
            return;
        }

        if (!node)
        {
            return;
        }

        print_inorder(node->left);
        std::cout << "(" << node->key << ":" << node->value << ") ";
        print_inorder(node->right);
    }

    void print_preorder(Node *node) const
    {
        if (node == root && !root)
        {
            std::cout << "()";
            return;
        }

        if (!node)
        {
            return;
        }

        std::cout << "(" << node->key << ":" << node->value << ") ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    void print_postorder(Node *node) const
    {
        if (node == root && !root)
        {
            std::cout << "()";
            return;
        }

        if (!node)
        {
            return;
        }

        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << "(" << node->key << ":" << node->value << ") ";
    }

    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        clear();
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        if (!root)
        {
            root = new Node(key, value);
            node_count++;
            return true;
        }

        return inserthelp(root, key, value);
    }

    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic
        if (!find(key))
            return false;

        root = removehelp(root, key);
        node_count--;
        return true;
    }

    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic

        return findhelp(root, key);
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        if (!find(key))
            throw std::runtime_error("Key not found in BST");

        return gethelp(root, key);
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        if (!find(key))
            throw std::runtime_error("Update error! Key not found in BST");

        updatehelp(root, key, value);
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        clearhelp(root);
        node_count = 0;
        root = nullptr;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic
        // return sizehelp(root);
        return node_count;
    }

    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return root == nullptr;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic

        if (!root)
            throw std::runtime_error("BST is empty");

        return find_minhelp(root);
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic

        if (!root)
            throw std::runtime_error("BST is empty");

        return find_maxhelp(root);
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        if (tolower(traversal_type) == 'd')
        {
            std::cout << "BST (Default): ";
            print_default(root);
        }
        else if (tolower(traversal_type) == 'p')
        {
            std::cout << "BST (Pre-order): ";
            print_preorder(root);
        }
        else if (tolower(traversal_type) == 'i')
        {
            std::cout << "BST (In-order): ";
            print_inorder(root);
        }
        else
        {
            std::cout << "BST (Post-order): ";
            print_postorder(root);
        }
    }
};

#endif // LISTBST_H