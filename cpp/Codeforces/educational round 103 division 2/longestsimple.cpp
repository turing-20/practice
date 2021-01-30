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
    vector<int> c;
    vector<int> a;
    vector<int> b;
    for(int i=0;i<n;i++)
    {
        int j;
        cin>>j;
        c.push_back(j);
    }
    for(int i=0;i<n;i++)
    {
        int j;
        cin>>j;
        a.push_back(j);
    }
    for(int i=0;i<n;i++)
    {
        int j;
        cin>>j;
        b.push_back(j);
    }
    int ans=0;

    for(int i=1;i<n;i++)
    {
        int same=0;
        for(int j=i+1;j<n;j++)
        {
            if(a[j]==b[j])
            {
                same=j-1;
                break;
            }
            else
                continue;
        }
        int distance=b[i]-a[i];
        for(int j=i+1;j<=same;j++)
        {
            distance+=b[j]-a[j];
        }
        ans=max(distance,ans);
    }
    cout<<ans<<endl;
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