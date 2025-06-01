# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
using namespace std;

int main(){
	int n;
	vector<string> v;
	
	cin>>n;
	while(n--){
		string temp;
		cin>>temp;
		v.push_back(temp);
	}
	//sort(v.begin(),v.end(),greater<>());
	sort(v.begin(),v.end(),[](string a,string b){
		return a>b;
	});
	string s="";
	for(int i=0;i<v.size();i++){
		s+=(v[i]);
	}
	cout<<s;
	
}

//有一个坑，字典序中的3和30比较30更大，但是拼接后303比330小，所以这里需要重写排序方案为a+b>b+a,即330>303