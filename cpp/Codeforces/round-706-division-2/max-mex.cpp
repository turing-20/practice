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
    ll k;
    cin >> n >> k;

    vector<int> a;

    for (int i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        a.push_back(c);
    }
    if (k == 0)
    {
        cout << n << endl;
        return;
    }
    int ans = n;
    int m = *max_element(a.begin(), a.end());

    if (m + 1 == n)
    {
        cout << n + k << endl;
        return;
    }

    if (m == n)
    {
        cout << n << endl;
        return;
    }

    if (m > n)
    {
        vector<int> b((m + 1), 0);
        for (int i = 0; i < n; i++)
        {
            b[a[i]] = 1;
        }

        int d = 0;
        for (int i = 0; i < (m + 1); i++)
        {
            if (b[i] != 1)
            {
                d = i;
                break;
            }
        }

        int g = ceil((d + m) / 2);

        if (b[g] == 1)
        {
            cout << n << endl;
            return;
        }
        else
        {
            cout << n + 1 << endl;
            return;
        }
    }
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