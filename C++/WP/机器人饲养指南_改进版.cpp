# include <iostream>
# include <algorithm>
# include <cstring>
using namespace std;

int main(){
	int m,n;
	int A[101];
	int dp[10001];
	memset(dp,0,sizeof(dp));
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>A[i];
	for(int i=1;i<=m;i++){
		for(int j=0;j+i<=n;j++){//本质是完全背包问题 
			dp[j+i]=max(dp[j+i],dp[j]+A[i]);
		}
	}
	cout<<dp[n];
	
	
	
}
