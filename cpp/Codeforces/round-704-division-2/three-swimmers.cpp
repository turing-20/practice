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

ll closest_multiple(ll a, ll b)
{
    if (a > b)
    {
        cout << "returned 0 for " << a << " " << b << endl;
        return 0;
    }

    ll c = b;
    b = b + a / 2;
    b = b - (b % a);

    if (b > c)
    {
        cout << "returned b-a " << b - a << " for " << a << " " << b << endl;
        return b - a;
    }
    cout << "returned b " << b << " for " << a << " " << b << endl;
    return b;
}

void solve()
{
    ll p;
    ll a;
    ll b;
    ll c;
    cin >> p;
    cin >> a;
    cin >> b;
    cin >> c;

    cout << min({p - closest_multiple(p, a), p - closest_multiple(p,b), p - closest_multiple(c, p)}) << endl;
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