# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

struct p{
	int pos;
}; 

int main(){
	//vector<p> v;
	int L,N;
	int minn=0;
	int maxn=0;
	
	cin>>L>>N;
	for(int i=1;i<=N;i++){
		int temp;
		
		cin>>temp;
		if(temp<=L/2){
			minn=max(minn,temp);
		}
		else{
			minn=max(minn,L-temp+1);
		}
		int maxtemp=max(temp,L-temp+1);
		maxn=max(maxn,maxtemp);
		//v.push_back(p{temp});
	}
	cout<<minn<<" "<<maxn;
}


//这道题需要读懂题目，看出其中隐藏的逻辑：
//最短的时间即所有士兵以桥的一半为基准，分别向两边撤，取最大需要的步数
//最长时间即一个士兵从桥的一边到另一边所需的最大步数，这里有个逻辑的hint，如果士兵相遇就掉头，其实可以看做士兵没有掉头继续向前走，对最后的结果是没有影响的