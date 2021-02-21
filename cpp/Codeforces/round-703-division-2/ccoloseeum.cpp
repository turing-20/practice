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
    priority_queue<int> pq;

    pq.push(1);
    pq.push(3);
    pq.push(0);
    pq.push(-1);
    cout << pq.top() << endl;
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