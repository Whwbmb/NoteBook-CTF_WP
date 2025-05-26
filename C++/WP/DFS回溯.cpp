#include <iostream>
#include <vector>
using namespace std;

void dfs(int n, int k,
         vector<int> &path,
         vector<bool> &used)
{
    if ((int)path.size() == k) {
        // path �����һ������Ϊ k �����У���ӡ��
        for (int x : path) cout << x;
        cout << "\n";
        return;
    }
    // ���γ��԰� i �ŵ���ǰ·��ĩβ
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
