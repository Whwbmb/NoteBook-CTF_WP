# include <iostream>
# include <cstring>
# include <algorithm>
using namespace std;

int n;
int dp[101][101];
int num[101][101];

int dfs(int i,int j){
	if(i<0||i>n-1||j<0||j>i)return 0;
	if(dp[i][j]!=-1)return dp[i][j];
	dp[i][j]=max(dp[i][j],dfs(i+1,j)+num[i][j]);
	dp[i][j]=max(dp[i][j],dfs(i+1,j+1)+num[i][j]);
	return dp[i][j];
}
int main(){
	memset(dp,-1,sizeof(dp));
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			cin>>num[i][j];
		}
	}
	cout<<dfs(0,0);
} 
