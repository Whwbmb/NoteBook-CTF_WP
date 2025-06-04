# include <iostream>
# include <cstring>
#include <algorithm>
using namespace std;

int dp[10001];
int n,m;
int num[101];


int dfs(int remain){
	if(remain==0)return 0;
	if(dp[remain]!=-1)return dp[remain];
	for(int temp=1;temp<=m&&temp<=remain;temp++){
			dp[remain]=max(dp[remain],dfs(remain-temp)+num[temp]);
	}
	return dp[remain];
	
	
}

int main(){
	memset(dp,-1,sizeof(dp));
	num[0]=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>num[i];
	}
	cout<<dfs(n);
}
