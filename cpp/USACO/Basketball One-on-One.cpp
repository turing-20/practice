//Jashanpreet Singh
#include<bits/stdc++.h>

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
    string s;
    cin >> s;
    cout << s[s.size()-2];
}
int main() {

    fastio();

    int t;
    // cin >> t;
    t=1;

    while(t--) {
        solve();
    }

    return 0;
}