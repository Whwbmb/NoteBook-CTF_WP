# include <iostream>
# include <cstring>
# include <algorithm>
using namespace std;

int main(){
	int T,M;
	int numt[101],numv[101];
	int dp[101]; 
	 
	memset(dp,-1,sizeof(dp)); 
	dp[0]=0;
	cin>>T>>M;
	for(int i=1;i<=M;i++)cin>>numt[i]>>numv[i];
	for(int i=1;i<=M;i++){
		for(int j=T;j>=numt[i];j--){
			dp[j]=max(dp[j],dp[j-numt[i]]+numv[i]);
		}
	}
	cout<<dp[T];
	
}
