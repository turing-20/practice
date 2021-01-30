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
    int k;
    cin>>n>>k;
    if(k==1)
    {
        cout<<1<<endl;
        return ;
    }
        
    if(n<=k)
        cout<<ceil(((double)k)/n)<<endl;
    else
    {
        double x=n+0.0;
        x=((double)k)/n;
        int a=1;
        double b=x;
        // cout<<x<<endl;
        while(x<1.0)
        {
            a+=1;
            x=b;
            x=x*a;
        }
        cout<<ceil(x)<<endl;
    }
}
int main() {

    fastio();

    int t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}