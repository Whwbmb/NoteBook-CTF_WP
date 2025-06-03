# include <iostream>
# include <algorithm>
using namespace std;

int n,t;
int tcost[103],mget[103];//初始化数组存储耗费和收获
int ans;//存储最终答案

void dfs(int pos,int tleft,int tans){
	if(tleft<0)return;//这里这一行其实已经没有意义了，因为后面的if判断已经过滤掉了tleft形参会为负数的情况
	else if(pos==n+1){
		max(ans,tans);
		return ;
	}
	else{
		dfs(pos+1,tleft,tans);
		if(tleft>=tcost[pos]){
			dfs(pos+1,tleft-tcost[pos],tans+mget[pos]);
		}
		return ;
	}
	
}

int main(){
	cin>>n>>t;
	for(int i=0;i<n;i++)cin>>tcost[i]>>mget[i];
	dfs(1,t,0);
	cout<<ans;
	return 0; 
}
