#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
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
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1)
    {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2)
    {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read Phil's words
        // Start your code here

        string card;
        in_file >> card;
        if (bst1->find(card))
        {
            bst1->update(card, 1 + bst1->get(card));
        }
        else
        {
            bst1->insert(card, 1);
        }

        // End your code here
    }
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read Claire's words
        // Start your code here

        string card;
        in_file >> card;
        if (bst2->find(card))
        {
            bst2->update(card, 1 + bst2->get(card));
        }
        else
        {
            bst2->insert(card, 1);
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here

    cout << "Phil's words:" << endl;
    bst1->print('I');
    cout << endl
         << endl;

    cout << "Claire's words:" << endl;
    bst2->print('I');
    cout << endl;

    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true)
    {
        string word;
        in_file >> word;

        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here

        string draw = word;

        if (bst1->find(draw))
        {
            cout << "Phil has " << draw << "!" << endl;
            if (bst1->get(draw) == 1)
            {
                bst1->remove(draw);
            }
            else
            {
                bst1->update(draw, bst1->get(draw) - 1);
            }
        }

        if (bst2->find(draw))
        {
            cout << "Claire has " << draw << "!" << endl;
            if (bst2->get(draw) == 1)
            {
                bst2->remove(draw);
            }
            else
            {
                bst2->update(draw, bst2->get(draw) - 1);
            }
        }

        if (bst1->empty())
        {
            if (bst2->empty())
            {
                cout << "Draw!" << endl;
                break;
            }
            else
            {
                cout << "Phil wins!" << endl;
                break;
            }
        }
        else
        {
            if (bst2->empty())
            {
                cout << "Claire wins!" << endl;
                break;
            }
        }

        cout << endl;
        cout << "Phil's remaining words:" << endl;
        bst1->print('I');
        cout << endl
             << endl;

        cout << "Claire's remaining words:" << endl;
        bst2->print('I');
        cout << endl;
        cout << endl;

        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}