# include <iostream>
# include <cstring>
# include <algorithm>
using namespace std;

int main(){
	int T,M;
	int numt[1001],numv[101];
	int dp[1001]; 
	 
	memset(dp,0,sizeof(dp)); 
	cin>>T>>M;
	for(int i=1;i<=M;i++)cin>>numt[i]>>numv[i];
	for(int i=1;i<=M;i++){
		for(int j=T;j>=numt[i];j--){
			dp[j]=max(dp[j],dp[j-numt[i]]+numv[i]);
		}
	}
	cout<<dp[T];
	
}
