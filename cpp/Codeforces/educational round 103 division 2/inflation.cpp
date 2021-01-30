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
    int ans = 0;
    vector<int> p;
    ll sum1=0;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        sum1+=a;
        p.push_back(a);
    }
    ll sum=p[0];
    // cout<<sum1<<endl;
    double K=k*0.01;
    for(int i=1;i<n;i++)
    {
        double c=((double)p[i])/sum;
        if(c<K)
        {
            sum+=p[i];
            continue;
        }
            
        else
        {
            sum+=(ceil(p[i]/K - sum));
        }
        sum+=p[i];
    }
    cout<<(sum-sum1)<<endl;
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