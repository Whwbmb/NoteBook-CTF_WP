# include <iostream>
# include <algorithm>
using namespace std;

int n,t;
int tcost[103],mget[103];
int mem[103][103]={-1};
//int ans;.

int dfs(int pos,int tleft){
	if(mem[pos][tleft]!=-1)return mem[pos][tleft];
	else if(pos==n+1)return mem[pos][tleft]=0;
	else{
		int dfs1,dfs2=-1e9;
		dfs1=dfs(pos+1,tleft);
		if(tleft>=tcost[pos]){
			//mem[pos+1][tleft-tcost[pos]]=mem[pos][tleft]+mget[pos];
			dfs2=dfs(pos+1,tleft-tcost[pos])+mget[pos];
		}
		return mem[pos][tleft]=max(dfs1,dfs2);
	}
}

int main(){
	cin>>n>>t;
	for(int i=0;i<n;i++)cin>>tcost[i]>>mget[i];
	cout<<dfs(1,t);
//	cout<<ans;
	
}
