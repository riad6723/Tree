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
#define SSort(name) sort(name.rbegin(),name.rend())
#define For(name,start,finish) for(int name=start;name<finish;name++)
#define Forr(name,start,finish) for(int name=start;name>=finish;name--)
#define fast_in_out ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);


int row[]={0,1,0,-1,-1,-1,1,1};
int col[]={1,0,-1,0,1,-1,-1,1};

const ll N=1e5+10;
const ll M=1e18+7;
const ll H=1e9+7;
const ll base=131;

ll logx(ll a,ll bs){return log(a)/log(bs);}
ll Max(ll a,ll b){if(a>b)return a;return b;}
ll Min(ll a,ll b){if(a>b)return b;return a;}
ll big_mul(ll a,ll b,ll m){ll x=0,y=a%m;while(b>0){if(b&1)x=(x+y)%m;y=(2*y)%m;b>>=1;}return x%m;}
ll big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=(x*y)%m;y=(y*y)%m;b>>=1;}return x%m;}
ll Big_mod(ll a,ll b,ll m){ll x=1,y=a%m;while(b>0){if(b&1)x=big_mul(x,y,m);y=big_mul(y,y,m);b>>=1;}return x%m;}
ll mod_inverse(ll a,ll m){return big_mod(a,m-2,m);}  //a^-1 mod m = a^(m-2) mod m
ll GCD(ll a,ll b){if(!a)return b;return GCD(b%a,a);}

int ara1[N];
int ara2[N];
vector<int> ans;
vector<bool> vis(N);
vector<int> level(N);
vector<vector<int> > vec(N);

void dfs1(int node,int cnt)
{
    vis[node]=true;
    level[node]=cnt;

    For(i,0,sz(vec[node]))
    {
        int p=vec[node][i];

        if(vis[p]==false)
            dfs1(p,cnt+1);
    }
}

void dfs2(int node,int odd,int even)
{
    int carry=0;

    if(level[node]&1)
        carry=odd;

    else
        carry=even;

    int p=carry%2;
    int q=ara1[node];

    q=q^p;


    if(q!=ara2[node])
    {
        ans.pb(node);

        if(level[node]&1)
            odd++;

        else
            even++;
    }

    For(i,0,sz(vec[node]))
    {
        int new_node=vec[node][i];

        if(level[new_node]>level[node])
            dfs2(new_node,odd,even);
    }
}

int main()
{
    fast_in_out;

    int n;
    cin>>n;

    For(i,1,n)
    {
        int a,b;
        cin>>a>>b;

        vec[a].pb(b);
        vec[b].pb(a);
    }


    For(i,0,n)
    {
        int a;
        cin>>a;

        ara1[i+1]=a;
    }

    For(i,0,n)
    {
        int a;
        cin>>a;

        ara2[i+1]=a;
    }

    dfs1(1,0);
    dfs2(1,0,0);

    cout<<sz(ans)<<endl;

    For(i,0,sz(ans))
    cout<<ans[i]<<endl;

    return 0;
}

