# include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,m,p,q;
	
	int k;
	
	cin>>n>>m>>p>>q;
	int *num=new int[p*q];
	
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			int temp;
			cin>>temp;
			num[i*q+j]=temp;
			
		
		}	
	}
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			cout<<num[i*q+j]<<" ";
		}
		cout<<endl;
	
	}
}

//c的实现方式，直接使用数组实现 

