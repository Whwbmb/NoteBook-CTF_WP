# include <iostream>
# include <cstring>
# include <algorithm>
using namespace std;

int n,k;
long long num[101][101];
long long dp[101][101][101];
bool v[101][101][101];


long long dfs(long long x,long long y, int p){
	if(x<0||x>n-1||y<0||y>x)return 0;
//	if(dp[x][y][p]!=-0x3f)return dp[x][y][p];
	if(v[x][y][p])return dp[x][y][p];
	
	if(p!=k){
		dp[x][y][p]=max(dp[x][y][p],dfs(x+1,y,p+1)+3*num[x][y]) ;
		dp[x][y][p]=max(dp[x][y][p],dfs(x+1,y+1,p+1)+3*num[x][y]) ;
		
	}
	dp[x][y][p]=max(dp[x][y][p],dfs(x+1,y,p)+num[x][y]) ;
	dp[x][y][p]=max(dp[x][y][p],dfs(x+1,y+1,p)+num[x][y]) ;
	v[x][y][p]=true;
	return dp[x][y][p];
}


int main(){
//	memset(v,false,sizeof(v));
	memset(dp,-0x3f,sizeof(dp));
	cin>>n>>k;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			cin>>num[i][j];
		}
	}
	cout<<dfs(0,0,0);
	
}


//注意num的取值是有负数的情况的