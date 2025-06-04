# include <iostream>
# include <cstring>
# include <algorithm>


using namespace std;
int N;
int num[10][10];
int ans=0;
int dp[10][10];
int dfs(int x,int y){
	if(x==0&&y==0)return 0;
//	if(x<0||y<0)return 0;
	if(dp[x-1,y-1]!=-1)return dp[x-1,y-1];
	if(x-1>=0){
	dp[x][y]=max(dp[x][y],dfs(x-1,y)+num[x-1][y]);
	num[x-1][y]=0;
	}
	if(y-1>=0){
	dp[x][y]=max(dp[x][y],dfs(x,y-1)+num[x][y-1]);
	num[x][y-1]=0;	
	}
	
	
	return dp[x][y];
	
} 



int main(){
	memset(dp,-1,sizeof(dp));
	cin>>N;
	
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			num[i][j]=0;
		}	
	}
	int x,y,n;
	while(true){
		cin>>x>>y>>n;
		if(x==0&&x==0&&n==0)break;
		else{
		num[x][y]=n;
		}
	} 
	ans+=dfs(N-1,N-1);
	ans+=dfs(N-1,N-1);
	
	
} 
