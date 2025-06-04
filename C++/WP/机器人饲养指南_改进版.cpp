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
			//下面这句可以理解为想要装下容量占用为i的这个物品，即要满足条件n-i>=j,也就是n-j>=i，否则i就存不进去了，然后遍历j的目的就是遍历能够容下大小为i的物品的情况下各种背包容量能够取到的最值
		for(int j=0;j+i<=n;j++){//��������ȫ�������� 
			dp[j+i]=max(dp[j+i],dp[j]+A[i]);//所以这里的j+i一定是小于等于n的，这里这样写就会出现一种情况，pre_j+i就有可能等于later_j,因为前者的j一开始比较小，当时已经加过物品价值了，后面如果j的值比较大，正好又等于了之前的那个j+i的值，就又加了一次物品的价值，对于一个完全背包问题没有问题，但是对于一个01背包问题的话就是错误的方法
		}
	}
	cout<<dp[n];
	
	
	
}
