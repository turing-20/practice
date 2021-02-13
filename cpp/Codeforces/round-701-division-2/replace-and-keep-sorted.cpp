//Jashanpreet Singh
#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
typedef long long int ll;

void fastio()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
int main()
{

    fastio();

    freopen("input.txt", "r", stdin);

    int n;
    int q;
    int k;
    cin >> n >> q >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> counts(n);
    for (int i = 1; i < (n - 1); i++)
    {
        counts[i] = a[i + 1] - a[i - 1] - 2;
    }

    vector<int> total_Counts(n);
    total_Counts[0] = 0;
    total_Counts[1] = counts[1];
    counts[n - 1] = 0;
    for (int i = 2; i < (n); i++)
    {
        total_Counts[i] += total_Counts[i - 1] + counts[i];
    }

    // for (int i = 1; i < n; i++)
    // {
    //     cout << counts[i] << " ";
    // }
    // cout << endl;

    // for (int i = 1; i < n; i++)
    // {
    //     cout << total_Counts[i] << " ";
    // }
    // cout << endl;
    while (q--)
    {
        int ans = 0;
        int l;
        int r;
        cin >> l >> r;

        if (l == r)
        {
            cout << k - 1 << endl;
            continue;
        }

        // for (int i = l - 1; i < r; i++)
        // {
        //     if (i == (l - 1))
        //     {
        //         ans += a[i + 1] - 2;
        //         continue;
        //     }
        //     if (i == (r - 1))
        //     {
        //         ans += k - a[i - 1] - 1;
        //         continue;
        //     }

        //     ans += a[i + 1] - a[i - 1] - 2;
        // }

        ans += a[l] - 2;
        ans += k - a[r - 2] - 1;
        if ((r - l) > 1)
        {
            // cout << ans << " hello " << endl;
            ans += total_Counts[r - 2] - total_Counts[l - 1];

            // cout << ans << " hi " << endl;
        }

        cout << ans << endl;
    }

    return 0;
}