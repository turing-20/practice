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
    cin>>s;
    int ans=0;
    int a=1;
    for(int i=1; i<s.length();i++)
    {
        if(s[i-1]==s[i])
        {
            a+=1;
            // cout<<"first"<<endl;
        }
        else
        {
            ans=max(a,ans);
            a=1;
            // cout<<"second"<<endl;
        }
    }
    ans=max(ans,a);
    cout<<ans;
}
int main() {

    fastio();
    #ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout); 
    #endif 
    int t;
    // cin >> t;
    t=1;

    while(t--) {
        solve();
    }

    return 0;
}