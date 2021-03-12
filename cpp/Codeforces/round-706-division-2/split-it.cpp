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
    int k;
    cin >> n >> k;

    string s;
    cin >> s;

    int r = 2 * k + 1;

    if (k == 0)
    {
        cout << "YES" << endl;
        return;
    }

    if (r > s.length())
    {
        cout << "NO" << endl;
        return;
    }

    int a = 0;

    for (int i = 0; i <= ((n / 2) - 1); i++)
    {
        if (s[i] == s[n - i - 1])
        {
            a = a + 1;
        }
        else
        {
            break;
        }
    }
    // a = (a * (a + 1));
    if (a >= k)
    {
        cout << "YES" << endl;
        return;
    }
    else
    {
        cout << "NO" << endl;
        return;
    }
    cout << a << endl;
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