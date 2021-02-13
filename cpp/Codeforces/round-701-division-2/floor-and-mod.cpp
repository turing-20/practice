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
    int x;
    int y;
    cin >> x >> y;
    ll ans = 0;

    for (int i = 2; i <= y; i++)
    {
        // cout << x / (i + 1) << "hello " << i << " " << endl;
        if (((x / (i + 1)) + 1) >= i)
        {
            ans += i - 1;
        }
        // ans += x / (i + 1);
    }

    cout << ans << endl;
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