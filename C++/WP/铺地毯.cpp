# include <iostream>
#include <vector>
using namespace std;

struct bl {
	int a,b,g,k;
//	bl(int a,int b,int g,int k){
//		this->a=a;
//		this->b=b;
//		this->g=g;
//		this->k=k;
//	}
	bl(int _a, int _b, int _g, int _k)
	  : a(_a)    // 用参数 _a “直接初始化”成员 a
	  , b(_b)
	  , g(_g)
	  , k(_k)
	{
	  // 这里已经完成了成员的初始化，函数体里通常留空或写额外逻辑
	}
};
bool check(bl q,int x,int y){
	if((q.a+q.g)>=x&&q.a<=x&&(q.b+q.k)>=y&&q.b<=y){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int n;
	vector<bl> q;
	int a,b,g,k;
	int x,y;
	
	
	cin>>n;
	while(n--){
		cin>>a>>b>>g>>k;
		q.emplace_back(a,b,g,k);
//		q.emplace_back(bl{a,b,g,k});
	}
	cin >>x>>y;
	int temp=q.size();
	while(temp--){
		if(check(q[temp],x,y)){
			cout<<temp+1;
			return 0;
		}
	}
	cout<<-1;
	return 0;


} 
