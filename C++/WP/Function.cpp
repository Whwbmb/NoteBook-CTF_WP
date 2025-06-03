# include <iostream>
# include <algorithm>
# include <iomanip>
# include <vector>
#include <cstring>
using namespace std;

long long dp[21][21][21];
struct n{
	long long a,b,c;
	long long  ans;
};

long long w(long long  a,long long b,long long  c){

	if(a<=0||b<=0||c<=0)return 1;
	if(a>20||b>20||c>20)return w(20,20,20);
	int ia = (int)a, ib = (int)b, ic = (int)c;
    if (dp[ia][ib][ic] != -1) {
        return dp[ia][ib][ic];
		}
	if(a<b&&b<c) return dp[ia][ib][ic]= w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c); 
	else return dp[ia][ib][ic]= w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
}

int main(){
	memset(dp,-1,sizeof(dp));
	long long  a,b,c;
	vector<n> v;
	while(true){
		cin>>a>>b>>c;
		if(a==-1&&b==-1&&c==-1)break;
		v.push_back(n{a,b,c,w(a,b,c)}); 
	}
	for(auto &elem:v){
		cout<<"w("<<elem.a<<", "<<elem.b<<", "<<elem.c<<")"<<" = "<<elem.ans<<endl;
	}
	
}

