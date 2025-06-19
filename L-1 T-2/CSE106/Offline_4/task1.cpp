#include <iostream>
#include <fstream>
#include "listBST.hpp"

#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst)
    {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c)
    {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here

        if (c == 'I')
        {
            int key;
            in_file >> key;
            if (bst->insert(key, key))
            {
                cout << "Key " << key << " inserted into BST, ";
            }
            else
            {
                cout << "Insertion failed! Key " << key << " already exists in BST, ";
            }
            bst->print();
            cout << endl;
        }
        else if (c == 'D')
        {
            int key;
            in_file >> key;
            if (bst->remove(key))
            {
                cout << "Key " << key << " removed from BST, ";
            }
            else
            {
                cout << "Removal failed! Key " << key << " not found in BST, ";
            }
            bst->print();
            cout << endl;
        }
        else if (c == 'F')
        {
            int key;
            in_file >> key;
            if (bst->find(key))
            {
                cout << "Key " << key << " found in BST." << endl;
            }
            else
            {
                cout << "Key " << key << " not found in BST." << endl;
            }
        }
        else if (c == 'V') // value of key
        {
            int key;
            in_file >> key;
            int value;
            try
            {
                value = bst->get(key);
                cout << "Value of key " << key << " is: " << value;
            }
            catch (const std::exception &e)
            {
                cout << "Get Method Error: Key " << key << " not found in BST." << endl;
            }
        }
        else if (c == 'U')
        {
            int key, value;
            in_file >> key >> value;
            try
            {
                bst->update(key, value);
                cout << "Value of key " << key << " updated to " << value;
            }
            catch (const std::exception &e)
            {
                cout << "Update Failed: Key " << key << " not found in BST." << endl;
            }
        }
        else if (c == 'C')
        {
            bst->clear();
            cout << "BST cleared" << endl;
        }
        else if (c == 'S')
        {
            cout << "Size: " << bst->size() << endl;
        }
        else if (c == 'E')
        {
            if (bst->empty())
                cout << "Empty" << endl;
            else
                cout << "Not empty" << endl;
        }
        else if (c == 'M')
        {
            char *choice = new char[5];

            in_file >> choice;

            if (strcmp(choice, "Min") == 0)
            {
                int mn;
                try
                {
                    mn = bst->find_min();
                    cout << "Minimum value: " << mn << endl;
                }
                catch (const std::exception &e)
                {
                    cout << "Find minimum: BST is empty." << endl;
                }
            }
            else
            {
                int mx;
                try
                {
                    mx = bst->find_max();
                    cout << "Maximum value: " << mx << endl;
                }
                catch (const std::exception &e)
                {
                    cout << "Find maximum: BST is empty." << endl;
                }
            }
            delete[] choice;
        }
        else if (c =='T')
        {
            char *choice = new char[5];
            in_file >> choice;

            

            if(strcmp(choice, "In") == 0)
            {
                bst->print('I');
            }
            else if(strcmp(choice, "Pre") == 0)
            {
                bst->print('P');
            }
            else if(strcmp(choice, "Post") == 0)
            {
                bst->print('O');
            }
            else 
            {
                bst->print();
            }
            cout << endl;

            delete[] choice;

        }
        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}
