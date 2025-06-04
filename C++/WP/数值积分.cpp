# include <iostream>
# include <vector>

using namespace std;
int b,c,l,r;

int f(int x){
	return x*x+b*x+c;
}

int main(){
	cin>>b>>c>>l>>r;
	int ans=0;
	for(int i=l;i<=r;i++){
		if(i%2==0)ans+=f(i);
	}
	ans*=2;
	cout<<ans;
	
	
}
