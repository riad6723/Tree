#include <bits/stdc++.h>
using namespace std;
#define N 200010

queue<int> Q;
vector<int> seq;
vector<vector<int> > vec(N);

int visit_adjacent_nodes(vector<int> &marked,int x)
{
    
    int cnt=0;
    
    for(int i=0;i<vec[x].size();i++)
    {
        int p=vec[x][i];
        
        if(marked[p]==1)
        return -1;
        
        if(!marked[p])
        {
            marked[p]=1;
            cnt++;
        }
        
    }
    
    return cnt;
    
}

bool check_sequence(int n)
{
    
    int cnt=0;
    Q.push(0);
    vec[1].push_back(0);
    vec[0].push_back(1);
    vector<int> marked(n+10);
    //marked[seq[0]]=1;
    
    for(int i=0;i<n;)
    {
        int n=seq[i];
        
        if(marked[n]==1&&cnt)
        {
            Q.push(n);
            cnt--;
            i++;
        }
        
        else if(!marked[n]&&cnt==0)
        {
            int p=Q.front();
            Q.pop();
            
            marked[p]=2;
            cnt=visit_adjacent_nodes(marked,p);//cout<<cnt<<endl;
            
        }
        
        else
        return false;
        
    }
    
    cnt=0;
    
    for(int i=1;i<=n;i++)
    {
        if(marked[i]==1)
        cnt++;
    }
    
    if(cnt==Q.size())
    return true;
    
    return false;
}

int main() 
{
    int n;
    cin>>n;
    
    
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
        
    }
    
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        seq.push_back(a);
    }
    
    
    bool p=check_sequence(n);//cout<<"d"<<endl;
    
    if(p==true)
    cout<<"Yes"<<endl;
    
    else
    cout<<"No"<<endl;
    
	return 0;
	
}

/*

10
1 2
1 3
1 4
2 5
3 9
3 6
4 7
4 8
9 10
1 4 2 3 8 7 5 6 9 10


*/