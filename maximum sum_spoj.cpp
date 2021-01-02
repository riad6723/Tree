#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N=1000010;
vector<ll> lazy_tree(N);
vector<pair<ll,pair<ll,ll> > > tree(N);


ll ans(ll a,ll b,ll tree_index)
{

	ll l=tree[tree_index].second.first;
	ll r=tree[tree_index].second.second;
	ll range=r-l+1;

	if(lazy_tree[tree_index])
    {

        tree[tree_index].first+=range*lazy_tree[tree_index];
        lazy_tree[2*tree_index]+=lazy_tree[tree_index];
        lazy_tree[2*tree_index+1]+=lazy_tree[tree_index];
        lazy_tree[tree_index]=0;

    }

	if(r<a||l>b)
	return 0;

	if(l>=a&&r<=b)
	return tree[tree_index].first;


	return ans(a,b,2*tree_index)+ans(a,b,2*tree_index+1);

}

void build_tree(ll l,ll r,ll tree_index)
{

	tree[tree_index].second.first=l;
	tree[tree_index].second.second=r;

	if(l==r)
	{

		tree[tree_index].first=0;
		return;

	}

	ll mid=(l+r)/2;

	build_tree(l,mid,2*tree_index);
	build_tree(mid+1,r,2*tree_index+1);

	tree[tree_index].first=0;

}

void update(ll a,ll b,ll tree_index,ll value)
{

	ll l=tree[tree_index].second.first;
	ll r=tree[tree_index].second.second;
	ll x=lazy_tree[tree_index];
	ll range=r-l+1;


	if(x)
	{

		tree[tree_index].first+=range*x;
		lazy_tree[2*tree_index]+=x;
		lazy_tree[2*tree_index+1]+=x;
		lazy_tree[tree_index]=0;

	}

	if(r<a||l>b)
	return;

	if(l>=a&&r<=b)
	{

		lazy_tree[2*tree_index]+=value;
		lazy_tree[2*tree_index+1]+=value;
		tree[tree_index].first+=range*value;
		return;

	}

	update(a,b,2*tree_index,value);
	update(a,b,2*tree_index+1,value);

	tree[tree_index].first=tree[2*tree_index].first+tree[2*tree_index+1].first;

}

int main()
{

	ll t;
	cin>>t;



	while(t--)
	{

		ll n,c;
		cin>>n>>c;

		lazy_tree.assign(N,0);
	    build_tree(1,n,1);

		while(c--)
		{

			ll a,b,value,f;

			cin>>f>>a>>b;

			if(!f)
			{
				cin>>value;
			    update(a,b,1,value);
			}
			else
			cout<<ans(a,b,1)<<endl;

		}

	}
    return 0;
}
