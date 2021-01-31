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
    int n;
    cin>>n;
    ll sum=0;
    switch(n%4)
    {
        case 0:
            sum=n;
            break;
        case 1:
            sum=1;
            break;
        case 2:
            sum=n+1;
            break;
        case 3:
            sum=0;
            break;
    }
    ll c=0;
    for(int i=0; i<(n-1);i++)
    {
        int a;
        cin>>a;
        c=c^a;
    }
    cout<<(sum^c);
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