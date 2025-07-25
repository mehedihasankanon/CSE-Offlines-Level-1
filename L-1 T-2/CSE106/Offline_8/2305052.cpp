#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string s1, s2;
int match_score, mismatch_penalty, gap_penalty;

bool match(char a, char b)
{
    return a == b;
    // if(a == 'C' && b == 'G' || a == 'G' && b == 'C') return true;
    // if(a == 'A' && b == 'T' || a == 'T' && b == 'A') return true;
    // return false;
}

void global(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    int dp[n + 5][m + 5];

    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = dp[i - 1][0] + gap_penalty;
    }
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = dp[0][j - 1] + gap_penalty;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int ch1 = dp[i - 1][j - 1];
            if (match(s1[i - 1], s2[j - 1]))
                ch1 += match_score;
            else
                ch1 += mismatch_penalty;

            int ch2 = dp[i - 1][j] + gap_penalty;
            int ch3 = dp[i][j - 1] + gap_penalty;

            dp[i][j] = max(ch1, max(ch2, ch3));
        }
    }

    int tn = n, tm = m;
    string t1, t2;
    while (n > 0 && m > 0)
    {
        if ((match(s1[n - 1], s2[m - 1]) && (dp[n][m] == dp[n - 1][m - 1] + match_score)) ||
            (!match(s1[n - 1], s2[m - 1]) && dp[n][m] == dp[n - 1][m - 1] + mismatch_penalty))
        {
            t1 += s1[n - 1];
            t2 += s2[m - 1];
            n--;
            m--;
        }
        else if (dp[n][m] == dp[n - 1][m] + gap_penalty)
        {
            t1 += s1[n - 1];
            t2 += '-';
            n--;
        }
        else
        {
            t1 += '-';
            t2 += s2[m - 1];
            m--;
        }
    }
    while (n > 0)
    {
        t1 += s1[n - 1];
        t2 += '-';
        n--;
    }
    while (m > 0)
    {
        t1 += '-';
        t2 += s2[m - 1];
        m--;
    }

    reverse(t1.begin(), t1.end());
    reverse(t2.begin(), t2.end());

    cout << endl
         << "Global Alignment:" << endl;
    cout << t1 << endl
         << t2 << endl
         << endl;

    cout << "Maximum Score: " << dp[tn][tm] << endl;
    return;
}

void local(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    int dp[n + 5][m + 5];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = 0;

    int max_score = 0;
    int max_i = 0, max_j = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int ch1 = dp[i - 1][j - 1];
            if (match(s1[i - 1], s2[j - 1]))
                ch1 += match_score;
            else
                ch1 += mismatch_penalty;

            int ch2 = dp[i - 1][j] + gap_penalty;
            int ch3 = dp[i][j - 1] + gap_penalty;

            dp[i][j] = max(0, max(ch1, max(ch2, ch3)));

            if (dp[i][j] > max_score)
            {
                max_score = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    n = max_i, m = max_j;
    string t1, t2;
    while (n > 0 && m > 0 && dp[n][m] > 0)
    {
        if ((match(s1[n - 1], s2[m - 1]) && (dp[n][m] == dp[n - 1][m - 1] + match_score)) ||
            (!match(s1[n - 1], s2[m - 1]) && dp[n][m] == dp[n - 1][m - 1] + mismatch_penalty))
        {
            t1 += s1[n - 1];
            t2 += s2[m - 1];
            n--;
            m--;
        }
        else if (dp[n][m] == dp[n - 1][m] + gap_penalty)
        {
            t1 += s1[n - 1];
            t2 += '-';
            n--;
        }
        else
        {
            t1 += '-';
            t2 += s2[m - 1];
            m--;
        }
    }

    reverse(t1.begin(), t1.end());
    reverse(t2.begin(), t2.end());

    cout << endl
         << "Local Alignment:" << endl;
    cout << t1 << endl
         << t2 << endl
         << endl;
    cout << "Maximum Score: " << max_score << endl;
    return;
}

int main()
{
    // freopen("input.txt", "r", stdin);

    cout << "Enter first Sequence: ";
    cin >> s1;
    cout << "Enter second sequence: ";
    cin >> s2;

    cout << "Enter match score: ";
    cin >> match_score;
    cout << "Enter mismatch penalty: ";
    cin >> mismatch_penalty;
    cout << "Enter gap penalty: ";
    cin >> gap_penalty;

    global(s1, s2);
    local(s1, s2);
}