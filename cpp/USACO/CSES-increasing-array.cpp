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
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        int b;
        cin >> b;
        a[i] = b;
    }

    ll ans = 0;

    // for (int i = 0; i < n; i++)
    // {
    //     cout << a[i] << " " << i << " " << endl;
    // }

    for (int i = 1; i < n; i++)
    {
        if ((a[i] - a[i - 1]) < 0)
        {
            // cout << (a[i] - a[i - 1]) << endl;
            ans += a[i - 1] - a[i];
            a[i] = a[i] + (a[i - 1] - a[i]);
        }
    }
    cout << ans;
}
int main()
{

    fastio();

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t;
    // cin >> t;
    t = 1;

    while (t--)
    {
        solve();
    }

    return 0;
}