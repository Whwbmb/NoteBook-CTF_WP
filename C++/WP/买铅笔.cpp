# include<iostream>
# include<algorithm>
using namespace std;

int number(int n,int n1){
	int n2=1;
	while(true){
		if(n1*n2>=n){
			return n2;
		}
		n2++;
	}
}

int main(){
	int n,n1,n11,n2,n22,n3,n33;
	int s1,s2,s3,smin;
	//smin=100000000;
	cin>>n>>n1>>n11>>n2>>n22>>n3>>n33;
	s1=number(n,n1)*n11;
	//if(s1<=smin)smin=s1;
	s2=number(n,n2)*n22;
	//if(s2<=smin)smin=s2;
	s3=number(n,n3)*n33;
	//if(s3<=smin)smin=s3;
	smin=min({s1,s2,s3});
	cout<<smin;
	
}
