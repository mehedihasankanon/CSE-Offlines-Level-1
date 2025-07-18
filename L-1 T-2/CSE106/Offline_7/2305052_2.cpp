#include <bits/stdc++.h>

using namespace std;

void cleanup(int **benches, int n, int b);

int main()
{
    // if (!freopen("input.txt","r",stdin)) {
    //     cerr << "Failed to open input.txt" << endl;
    //     return 1;
    // }
    // if (!freopen("output.txt","w",stdout)) {
    //     cerr << "Failed to open output.txt" << endl;
    //     return 1;
    // }

    int n, b;
    cin >> n >> b;

    int **benches = new int *[b];
    for (int i = 0; i < b; i++)
    {
        benches[i] = new int[n / b];
        for (int j = 0; j < n / b; j++)
        {
            cin >> benches[i][j];
        }
    }

    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < n / b; j++)
        {
            if (benches[i][j] == 1 || benches[i][j] == 2)
            {
                if (j < n / b - 1)
                {
                    if (benches[i][j + 1] == 1 || benches[i][j + 1] == 2)
                    {
                        cout << "false" << endl;
                        cleanup(benches, n, b);
                        return 0;
                    }
                    benches[i][j + 1] = -1;
                }
                if (benches[i][j] == 2)
                {
                    if (j && (benches[i][j - 1] == 1 || benches[i][j - 1] == 2))
                    {
                        cout << "false" << endl;
                        cleanup(benches, n, b);
                        return 0;
                    }
                    benches[i][j - 1] = -1;
                }
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < n / b; j++)
        {
            // cout << benches[i][j] << " ";
            cnt += (benches[i][j] == 0);
        }
        // cout << endl;
    }

    int m;
    cin >> m;

    if (cnt >= m)
    {
        cout << "true" << endl;
    }
    else
        cout << "false" << endl;

    cleanup(benches, n, b);
    return 0;
}

void cleanup(int **benches, int n, int b)
{

    for (int i = 0; i < b; i++)
    {
        delete[] benches[i];
    }
    delete[] benches;
}