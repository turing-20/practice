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
        cout << 1 << endl;
        return;
    }

    if (n > 1 && n < 4)
    {
        cout << "NO SOLUTION" << endl;
        return;
    }

    if (n == 4)
    {
        cout << "2 4 1 3";
        return;
    }

    for (int i = n; i > 0; i = i - 2)
    {
        cout << i << " ";
    }

    for (int i = n - 1; i > 0; i = i - 2)
    {
        cout << i << " ";
    }
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