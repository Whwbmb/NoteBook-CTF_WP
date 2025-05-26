#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


bool half(unsigned long long n,unsigned long long k){
	if(1ll<<(n-1)>k) return true;//С��һ��
	else return false;//����һ�� 
}


int main(){
	unsigned long long n,k;
	cin>>n>>k;
	string v="";
	
	while(true){
		if(n==1){
			if(k==0) v+='0';
			else v+='1';
			break;
		}
		if(half(n,k)){
			n--;
			v+='0';
		}
		else{
			//k=(1ll<<n)-k-1;
			k=(1ll<<(n-1))-(k-(1ll<<(n-1)))-1;
			n--;
			v+='1';
		}
	}
	cout<<v;
	
}

//很容易出现越界问题，需要注意不要爆long long
