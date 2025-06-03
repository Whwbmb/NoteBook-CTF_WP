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

