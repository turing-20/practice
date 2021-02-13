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
    ll a;
    ll b;
    cin >> a >> b;
    ll c = a;
    ll count = MOD;

    for (int i = 0;; i++, b++)
    {
        if (b == 1)
        {
            continue;
        }

        ll steps = 0;
        c = a;
        while (c > 0)
        {
            steps++;
            c = c / b;
        }

        if ((i + steps) <= count)
        {
            // cout << b << " " << i + steps << " hello " << endl;
            count = i + steps;
            continue;
        }
        else
        {
            // cout << b << " " << i + steps << " hello  hi" << endl;
            break;
        }
    }

    cout << count << endl;
}
int main()
{

    fastio();

    freopen("input.txt", "r", stdin);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}