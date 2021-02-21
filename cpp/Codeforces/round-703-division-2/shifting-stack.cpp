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
void solve()
{
    int n;
    cin >> n;

    vector<ll> h(n);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }
    int flag = 1;

    // h[1] += h[0];

    // h[0] = 0;

    // if (h[1] == 0)
    // {
    //     cout << "NO" << endl;
    //     return;
    // }

    for (int i = 1; i < n + 1; i++)
    {
        if ((h[i - 1] - i + 1) >= 0)
        {
            if (i == n)
                break;
            h[i] += h[i - 1] - i + 1;
        }
        else
        {
            flag = 0;
            break;
        }
    }
    // for (int i = 1; i < n; i++)
    // {
    //     if (h[i] <= 0)
    //     {
    //         cout << "NO" << endl;
    //         return;
    //     }
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << h[i] << " ";
    // }
    // cout << endl;
    // cout << "YES" << endl;
    if (flag == 0)
    {
        cout << "NO" << endl;
        return;
    }
    else
    {
        cout << "YES" << endl;
        return;
    }
    return;
}
int main()
{

    fastio();

    // freopen("input.txt", "r", stdin);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}