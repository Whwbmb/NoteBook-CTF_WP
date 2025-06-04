# include <iostream>
# include <cstring>
using namespace std;

int T,M;
int dp[101][1001];
int costtime[101];
int gvalue[101];


int dfs(int pos,int ltime){
	if(ltime<0)return 0;
	if(pos>M-1)return 0;
	if(dp[pos][ltime]!=-1)return dp[pos][ltime]; 


	dp[pos][ltime]=max(dp[pos][ltime],dfs(pos+1,ltime));
	if(costtime[pos]<=ltime)
	dp[pos][ltime]=max(dp[pos][ltime],dfs(pos+1,ltime-costtime[pos])+gvalue[pos]);
	
	return dp[pos][ltime];
}

int main(){
	memset(dp,-1,sizeof(dp));
	cin>>T>>M;
	for(int i=0;i<M;i++){
		cin>>costtime[i]>>gvalue[i];
	}
	cout<<dfs(0,T);
}
