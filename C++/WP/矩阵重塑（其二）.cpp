# include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> op1(vector<vector<int>> num,int p,int q) {
	vector<vector<int>> new_num(p,vector<int> (q));
	int k;
	for(int i=0;i<num.size();i++){
		for(int j=0;j<num[0].size();j++){
			int k=i*num[0].size()+j;
			new_num[k/q][k%q] =num[i][j];
//			cout<<"debug"<<new_num[k/q][k%q]<<"debug";
		
		}
	}
//	for(auto &row:new_num){
//		for(auto &elem:row){
//			cout<<elem<<" ";
//		}
//		cout<<endl;
//	}
		return new_num; 
}

vector<vector<int>> op2(vector<vector<int>> num) {
	vector<vector<int>> new_num(num[0].size(),vector<int>(num.size()));
	for(int i=0;i<num.size();i++){
		for(int j=0;j<num[0].size();j++){
			new_num[j][i]=num[i][j];
		}
	}
//		for(auto &row:new_num){
//		for(auto &elem:row){
//			cout<<elem<<" ";
//		}
//		cout<<endl;
//	}
		return new_num; 
}
int op3(vector<vector<int>> num,int a,int b) {
//		cout<<"debug:"<<endl;
//		cout<<endl<<num[a][b];
		return num[a][b]; 
	
}

int main(){
	int n,m,t;	
	cin>>n>>m>>t;
	vector<vector<int>> num(n,vector<int>(m));
	vector<int>ans;
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>num[i][j];
		}
	}
	while(t--){
		int op,a,b;
		cin>>op>>a>>b;
		switch(op){
			case 1:
				num=op1(num,a,b); 
				break;
			case 2:
				num=op2(num);
				break;
			default:
				ans.push_back(op3(num,a,b));
		}	
	}
	for(auto &elem:ans){
		cout<<elem<<endl;
	}
		
}
//最好按照题目给的提示来程序，方便后面的题去调用之前题已经写好的东西，否则可能需要重新再写一遍
//函数部分容易写错几个地方：比如转置的部分，重新生成的矩阵大小变了，不能在用形参的大小了


//测试数据：
// 输入：
// 3 2 3
// 1 2
// 3 4
// 5 6
// 3 0 1
// 1 2 3
// 3 1 2

// 输出：
// 2
// 6

// 输入：
// 3 2 5
// 1 2
// 3 4
// 5 6
// 3 1 0
// 2 0 0
// 3 1 0
// 1 3 2
// 3 1 0

// 输出：
// 3
// 2
// 5