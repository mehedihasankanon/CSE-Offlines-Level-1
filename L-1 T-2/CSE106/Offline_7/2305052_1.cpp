#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define dbg(x) cout << __LINE__ << " " << #x << " " << x << endl

int main()
{

    // if (!freopen("input.txt", "r", stdin))
    // {
    //     cerr << "Failed to open input.txt" << endl;
    //     return 1;
    // }
    // if (!freopen("output.txt", "w", stdout))
    // {
    //     cerr << "Failed to open output.txt" << endl;
    //     return 1;
    // }

    int n, k;
    cin >> n >> k;

    if (k > n)
    {
        cout << -1 << endl;
        return 0;
    }

    ll *load = new ll[n];
    for (int i = 0; i < n; i++)
    {
        cin >> load[i];
    }

    ll l = 0, r = 1e18;
    while (r - l > 1)
    {
        ll mid = l + (r - l) / 2;

        ll cnt = 1, curr_workload = 0;
        int it = 0;
        bool possible = true;
        while (it < n)
        {
            if (load[it] > mid)
            {
                possible = !possible;
                break;
            }

            if (curr_workload + load[it] <= mid)
            {
                curr_workload += load[it++];
            }
            else
            {
                cnt++;
                curr_workload = load[it++];
            }
        }

        // dbg(mid);
        // dbg(cnt);

        if (possible && cnt <= k)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }

    cout << r << endl;

    delete[] load;
}