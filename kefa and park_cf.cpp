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
#define sz(name) name.size()
#define len(name) name.length()
#define ig cin.ignore()
#define sc1(name) scanf("%d",&name)
#define sc2(name1,name2) scanf("%d%d",&name1,&name2)
#define sc3(name1,name2,name3) scanf("%d%d%d",&name1,&name2,&name3)
#define scl1(name) scanf("%lld",&name)
#define scl2(name1,name2) scanf("%lld%lld",&name1,&name2)
#define scl3(name1,name2,name3) scanf("%lld%lld%lld",&name1,&name2,&name3)
#define Sort(name) sort(name.begin(),name.end())
#define For(name,start,finish) for(int name=start;name<finish;name++)
#define Forr(name,start,finish) for(int name=start;name>=finish;name--)
#define fast_in_out ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);


int row[]={0,1,0,-1};
int col[]={1,0,-1,0};

const ll N=1e5+10;
const ll M=1e18+7;
const ll H=1e9+9;
const ll base=131;

ll logx(ll a,ll bs){return log(a)/log(bs);}
ll Max(ll a,ll b){if(a>b)return a;return b;}
ll Min(ll a,ll b){if(a>b)return b;return a;}
ll big_mul(ll a,ll b,ll m){ll x=0,y=a%m;while(b>0){if(b&1)x=(x+y)%m;y=(2*y)%m;b>>=1;}return x%m;}
ll big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=(x*y)%m;y=(y*y)%m;b>>=1;}return x%m;}
ll Big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=big_mul(x,y,m);y=big_mul(y,y,m);b>>=1;}return x%m;}
ll mod_inverse(ll a,ll m){return big_mod(a,m-2,m);}  //a^-1 mod m = a^(m-2) mod m
ll GCD(ll a,ll b){if(!a)return b;return GCD(b%a,a);}

int m,ans;
vector<bool> vis1(N);
vector<bool> vis2(N);
vector<bool> leaf(N);
vector<bool> cat(N);
vector<vector<int> > vec(N);


void dfs1(int curr_node,int x)
{
    vis1[curr_node]=true;

    for(int i=0;i<sz(vec[curr_node]);i++)
    {
        int new_node=vec[curr_node][i];

        if(vis1[new_node]==false)
            dfs1(new_node,x+1);

    }

    if(curr_node!=1 And sz(vec[curr_node])==1)
        leaf[curr_node]=true;

}

void dfs2(int curr_node,int pre_value,int mx)
{
    vis2[curr_node]=true;


    if(cat[curr_node]==true)
        pre_value++;

    else
    pre_value=0;

    mx=max(mx,pre_value);

    if(leaf[curr_node]==true)
    {
        if(mx<=m)
            ans++;

        return;
    }

    For(i,0,sz(vec[curr_node]))
    {
        int new_node=vec[curr_node][i];

        if(vis2[new_node]==false)
            dfs2(new_node,pre_value,mx);
    }

}


int main()
{

    fast_in_out;


    int n;
    cin>>n>>m;


    For(i,0,n)
    {
        int a;
        cin>>a;

        if(a)
            cat[i+1]=true;
    }

    For(i,0,n-1)
    {
        int a,b;
        cin>>a>>b;

        vec[a].pb(b);
        vec[b].pb(a);
    }


    dfs1(1,1);
    dfs2(1,0,0);


    cout<<ans<<endl;


    return 0;
}

/*

7 3
1 1 1 1 1 0 1
1 2
1 3
2 4
3 5
5 6
6 7

*/
