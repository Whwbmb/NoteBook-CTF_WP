#include <iostream>
#include <vector>
using namespace std;

void dfs(int n, int k,
         vector<int> &path,
         vector<bool> &used)
{
    if ((int)path.size() == k) {
        // path 里就是一个长度为 k 的排列，打印它
        for (int x : path) cout << x;
        cout << "\n";
        return;
    }
    // 依次尝试把 i 放到当前路径末尾
    for (int i = 1; i <= n; ++i) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(i);
        dfs(n, k, path, used);
        path.pop_back();
        used[i] = false;
    }
}

int main(){
    int n = 9, k = 3;
    vector<bool> used(n+1, false);
    vector<int> path;
    dfs(n, k, path, used);
    return 0;
}
