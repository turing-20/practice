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

    vector<pair<int, int>> a(n);
    vector<int> b(n);
    vector<int> c(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first >> a[i].second;
        b[i] = a[i].first;
        c[i] = a[i].second;
    }
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    if (n % 2 == 1)
    {
        cout << 1 << endl;
        return;
    }

    int d = n / 2;

    int x1 = b[d];
    int x2 = b[d - 1];

    int y1 = c[d];
    int y2 = c[d - 1];

    ll x3 = (abs(x1 - x2) + 1LL);
    ll x4 = (abs(y1 - y2) + 1LL);

    ll x5 = x3 * x4;
    // cout << "hello " << (abs(x1 - x2)) << " " << (abs(y1 - y2)) << endl;
    // cout << "hi " << d << endl;
    cout << x5 << endl;
    return;
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