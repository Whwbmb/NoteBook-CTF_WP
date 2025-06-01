# include <iostream>
# include <vector>
# include <cmath>
using namespace std;

int main(){
	int n;
	vector<int> a;
	int ans=0;
	
	cin>>n;
	if(n==1){
		cout<<0;
		return 0;
	}
	while(n--){
		int temp;
		
		cin>>temp;
		a.push_back(temp);
	}
	n=a.size()/2;
	while(true){
		ans+=(abs(a[n-1]-a[a.size()-n]));
		n--;
		if(n==0) break;
	}	
	
	if(ans%2==0) cout<<ans/2;
	else cout<<-1;
	
} 

//代码有问题，并非这样求解，需要根据公式找突破口