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
    ll y;
    ll x;

    cin >> y >> x;

    ll m = max(y, x);

    ll a = (m) * (m - 1) + 1;

    if (x == y)
    {
        cout << a << endl;
        return;
    }

    if (m % 2 == 0)
    {
        if (y > x)
        {
            cout << a + abs(y - x) << endl;
            return;
        }
        else
        {
            cout << a - abs(x - y) << endl;
            return;
        }
    }
    else
    {
        if (y > x)
        {
            cout << a - abs(x - y) << endl;
            return;
        }
        else
        {
            cout << a + abs(x - y) << endl;
            return;
        }
    }
}
int main()
{

    fastio();

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}