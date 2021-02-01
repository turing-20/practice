//Jashanpreet Singh
#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define ll long long int

void fastio()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
void solve()
{
    ll n;
    cin >> n;
    ll a = (n * (n + 1)) / 2;
    if (a % 2 == 1)
    {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    ll b = a / 2LL;
    ll c = b;
    vector<ll> numbers(n + 1);
    // cout << c << endl;
    ll first_set_total = 0;
    ll second_set_total = 0;

    for (ll i = n; i > 0; i--)
    {
        if (c == 0)
        {
            break;
        }
        else
        {
            if (c - i >= 0)
            {
                // cout << c - i << endl;
                c = c - i;
                first_set_total += 1;
                numbers[i] = 1;
            }
        }
    }

    cout << first_set_total << endl;

    for (ll i = 1; i <= n; i++)
    {
        if (numbers[i] == 1)
        {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << (n - first_set_total) << endl;
    for (ll i = 1; i <= n; i++)
    {
        if (numbers[i] == 0)
        {
            cout << i << " ";
        }
    }
}
int main()
{

    fastio();

    // freopen("input.txt", "r", stdin);

    int t;
    // cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }

    return 0;
}