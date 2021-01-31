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
    ll n;
    cin>>n;
    cout<<n<<" ";
    while(n>1)
    {
        if(n%2==0)
        {
            n=n/2;
            cout<<n<<" ";
            continue;
        }
        else
        {
            n=n*3+1;
            cout<<n<<" ";
            continue;
        }
    }

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