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

    int l = 0;
    int r = n - 1;
    int sm = 0;
    cout << "? " << l + 1 << " " << r + 1 << endl;
    cin >> sm;
    while (l < r)
    {
        // cout << "? " << l + 1 << " " << r + 1 << endl;

        // cin >> sm;

        int m = (l + r) / 2;

        int check;

        cout << "? " << l + 1 << " " << m + 1 << endl;

        cin >> check;

        if (check == sm)
        {
            r = m;
        }
        else
        {
            if (sm > m)
            {
                r = m;
            }
            else
            {
                l = m + 1;
            }
            sm = check;
        }

        if (l == r)
        {
            cout << "! " << l + 1 << endl;
        }
    }

    cout.flush();
    return;
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