#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define ps push
#define pf push_front
#define mp make_pair
#define And &&
#define Or ||
#define inf INT_MAX
#define ppb pop_back
#define ppf pop_front
#define ig cin.ignore()
#define Sort(name) sort(name.begin(),name.end())
#define For(name,start,finish) for(int name=start;name<finish;name++)
#define fast_in_out ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

//int row[]={-1,0,1,0};
//int col[]={0,1,0,-1};

const int N=1e5+10;
const int M=1e9+9;
ll Max(ll a,ll b){if(a>b)return a;return b;}
ll big_mul(ll a,ll b,ll m){ll x=0,y=a%m;while(b>0){if(b&1)x=(x+y)%m;y=(2*y)%m;b>>=1;}return x%m;}
ll big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=(x*y)%m;y=(y*y)%m;b>>=1;}return x%m;}
ll Big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=big_mul(x,y,m);y=big_mul(y,y,m);b>>=1;}return x%m;}
ll mod_inverse(ll a,ll m){return big_mod(a,m-2,m);}


vector<int> vec(N);



int main()
{
	fast_in_out;


    double n,s;
    cin>>n>>s;

    For(i,1,n)
    {
        int a,b;
        cin>>a>>b;
        vec[a]++;
        vec[b]++;
    }

    double cnt=0;

    For(i,1,n+1)
    {
        if(vec[i]==1)
        cnt++;
    }

    printf("%.18lf\n",(s/cnt)*2.00);

	return 0;

}
