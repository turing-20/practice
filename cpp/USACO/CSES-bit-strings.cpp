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
    ll n;
    cin >> n;

    ll ans = 1;
    n = n % MOD;

    ll x = 2;

    while (n)
    {
        if (n & 1)
        {
            ans = (ans * x) % MOD;
        }

        n = n >> 1;

        x = (x * x) % MOD;
    }

    cout << ans << endl;
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