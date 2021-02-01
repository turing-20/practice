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
    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }
    if (n == 2)
    {
        cout << 0 << endl;
        cout << 6 << endl;
        return;
    }
    cout << 0 << endl;
    cout << 6 << endl;
    for (int i = 3; i <= n; i++)
    {
        ll p = i * i;
        ll j = i - 2, k = p * (p - 1) / 2;
        k -= 8 * j * (j + 1) / 2;
        cout << k << "\n";
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