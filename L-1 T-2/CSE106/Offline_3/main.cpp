#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" << endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    // freopen("test_input_1.txt", "r", stdin); // Test Case 1
    freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;

    int timestamp[10005] = {0}; // array for storing timestamps for the patients

    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic

        cout << "Operation " << i << " ";

        int op;
        cin >> op;
        if (op == 1)
        {
            int id, st;
            cin >> id >> st;
            timestamp[id] = st;
            cout << "(Arrival " << id << " " << st << "): ";
            if (Q1->empty() && Q2->empty())
            {
                if (Q->empty())
                {
                    int q = randomQueue();
                    if (q == 1)
                        Q1->enqueue(id);
                    else
                        Q2->enqueue(id);
                }
                else
                {
                    cout << endl;
                    Q->enqueue(id);
                }
            }
            else
            {
                cout << endl;
                if (Q1->empty())
                {
                    Q1->enqueue(id);
                }
                else if (Q2->empty())
                {
                    Q2->enqueue(id);
                }
                else
                {
                    if (timestamp[Q1->back()] < timestamp[Q2->back()])
                    {
                        Q1->enqueue(id);
                    }
                    else
                    {
                        Q2->enqueue(id);
                    }
                }
            }
        }
        else if (op == 2)
        {
            int id, st;
            cin >> id >> st;
            cout << "(Leave " << id << " " << st << "):" << endl;
            timestamp[id] = 0;

            class Helper
            {
            public:
                static void removal(Queue *q, int id)
                {
                    if (q->empty())
                        return;

                    if (q->front() == id)
                    {
                        q->dequeue();
                        return;
                    }

                    int head = q->front(), t = q->front();
                    while (t != id)
                    {
                        q->dequeue();
                        q->enqueue(t);
                        t = q->front();
                        if (t == head)
                        {
                            return;
                        }
                    }
                    q->dequeue();
                    t = q->front();
                    while (t != head)
                    {
                        q->dequeue();
                        q->enqueue(t);
                        t = q->front();
                    }
                    return;
                }
            };

            Helper::removal(Q1, id);
            Helper::removal(Q2, id);
            Helper::removal(Q, id);
        }
        else if (op == 3)
        {
            cout << "(Merge):" << endl;
            int pt1 = Q1->front(), pt2 = Q2->front();
            while (pt1 != -1 && pt2 != -1)
            {
                if (timestamp[pt1] < timestamp[pt2])
                {
                    Q1->dequeue();
                    Q->enqueue(pt1);
                    pt1 = Q1->front();
                }
                else
                {
                    Q2->dequeue();
                    Q->enqueue(pt2);
                    pt2 = Q2->front();
                }
            }

            while (pt1 != -1)
            {
                Q1->dequeue();
                Q->enqueue(pt1);
                pt1 = Q1->front();
            }
            while (pt2 != -1)
            {
                Q2->dequeue();
                Q->enqueue(pt2);
                pt2 = Q2->front();
            }
        }
        else if (op == 4)
        {
            cout << "(Split):" << endl;
            int fl = 0;
            while (!Q->empty())
            {
                int t = Q->dequeue();
                if (!fl)
                {
                    Q1->enqueue(t);
                }
                else
                {
                    Q2->enqueue(t);
                }
                fl = 1 - fl;
            }
        }
        else if (op == 5)
        {
            cout << "(Departure): ";
            if (!(Q1->empty() && Q2->empty()))
            {
                if (Q1->empty())
                {
                    Q2->dequeue();
                    cout << endl;
                }
                else if (Q2->empty())
                {
                    Q1->dequeue();
                    cout << endl;
                }
                else
                {
                    int t = randomQueue();
                    if (t == 1)
                        Q1->dequeue();
                    else
                        Q2->dequeue();
                }
            }
            else
            {
                if (!Q->empty())
                {
                    cout << endl;
                    Q->dequeue();
                }
            }

        } // other commands are gonna get ignored

        cout << "Q1: " << Q1->toString() << endl
             << "Q2: " << Q2->toString() << endl
             << "Q: " << Q->toString() << endl;

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}