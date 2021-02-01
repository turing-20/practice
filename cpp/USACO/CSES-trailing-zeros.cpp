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

    ll ans = 0;

    // vector<ll> c(n+1);

    for (ll i = 5; n / i >= 1; i = i * 5)
    {
        ans += n / i;
    }

    cout << ans;
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