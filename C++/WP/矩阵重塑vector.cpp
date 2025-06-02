# include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,m,p,q;
	vector<vector<int>> num;
	int k;
	
	cin>>n>>m>>p>>q;
	num.resize(p);
	
	for(int i=0;i<p;i++){
		int temp;
		for(int j=0;j<q;j++){
			cin>>temp;
			num[i].push_back(temp); 
		}
			
	}
	for(auto &row:num){
		for(auto &elem:row){
			cout<<elem<<" "; 
		}
		cout<<endl;
	}
	

}

//c的实现方式，直接使用数组实现 

