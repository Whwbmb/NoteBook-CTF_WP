## 数据规模
- int类型大概 2.1×10⁹ 就会爆
- long long 类型大概 9.2×10¹⁸ 会爆


## 爆long long
对于数据级别位2^64的情况，会出现long long溢出，在进行运算的时候就需要将其涉及到的运算转化为2^63级别

例如下下面的这个例子：
```c++
k=(1ll<<n)-k-1;
```
需要修改为
```c++
k=(1ll<<(n-1))-(k-(1ll<<(n-1)))-1;
```

## 对于long long 也容纳不下的大数据，需要使用高级数据体重写计算：

```c++
#include <iostream>
#include <vector>
using namespace std;


vector<int> addBig(const vector<int>& A, const vector<int>& B) {
    int n = (int)A.size();
    int m = (int)B.size();
    int len = max(n, m);
    vector<int> C;
    C.reserve(len + 1);  

    int carry = 0;
    for (int i = 0; i < len; i++) {
        int a_digit = (i < n ? A[i] : 0);
        int b_digit = (i < m ? B[i] : 0);
        int sum = a_digit + b_digit + carry;
        C.push_back(sum % 10);
        carry = sum / 10;
    }
    if (carry) {
        C.push_back(carry);
    }
    return C;
}

int main() {
    int N;
    cin >> N;
    if (N <= 0) return 0;

    if (N == 1) {
        cout << 1;
        return 0;
    }
    if (N == 2) {
        cout << 2;
        return 0;
    }

    vector<vector<int>> dp(N + 1);

    dp[1] = {1};  
    dp[2] = {2};  

    for (int i = 3; i <= N; i++) {
        dp[i] = addBig(dp[i - 1], dp[i - 2]);
    }

    const vector<int>& ans = dp[N];
    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    return 0;
}
```

通过数组的形式进行重新计算
最后再使用数组进行输出







