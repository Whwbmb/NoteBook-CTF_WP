//# include<iostream>
//# include <algorithm>
//# include <vector>
//using namespace std;
//
//int main(){
//	int n;
//	long long  ans=0;
//	
//	cin>>n;
//	vector<long long> v;
//	
//	while(n--){
//		long long tmp;
//		cin>>tmp;
//		v.push_back(tmp);
//	}
//	while(v.size()!=1){
//		sort(v.begin(),v.end(),greater<long long>());
//		
//		ans+=v.at(v.size()-2);
//		ans+=v.at(v.size()-1);
//		v[v.size()-2]+=v[v.size()-1];
//		v.pop_back();
//		
//	}
//	
//	cout<<ans;
//}

#include <iostream>
#include <queue>
using namespace std;

int main(){
    int n;
    cin >> n;

    // min-heap��greater<long long> ��֤��Сֵ�� top()
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    
    long long x;
    for(int i = 0; i < n; i++){
        cin >> x;
        pq.push(x);
    }

    long long ans = 0;
    while(pq.size() > 1){
        // ȡ��������С��
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        long long s = a + b;
        ans += s;
        // �ϲ���Ŀ��ٷŻض���
        pq.push(s);
    }

    cout << ans;
    return 0;
}


