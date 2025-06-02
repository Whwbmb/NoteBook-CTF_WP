# include <iostream>
#include <vector>
using namespace std;

int main(){
	const int maxn=10001;
	int n,m,p,q;
	int num[maxn][maxn];
	int k;
	
	cin>>n>>m>>p>>q;
	for(int i=0;i<n*m;i++){
		k=i;
		cin>>num[k/n][k%n];
		cout<<num[k/n][k%n];
	}
//	for(int i=0;i)
}
