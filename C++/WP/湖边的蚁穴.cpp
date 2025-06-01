#include <iostream>
#include <vector>

using namespace std;
struct n{
    long long s;
    bool visit;
};
int main(){
    int N;
    int start;
    int cnt = 0;
    bool iscnt = false;
    bool init = false;
    vector<n> v;
    long long ans = 0;

    cin >> N;
    int NN = N;
    while (N--) {
        long long temp;
        cin >> temp;
        v.push_back(n{temp, false});
        if (temp != 0 && !init) {
            start = v.size() - 1;
            init = true;
        }
    }

    if (!init) {
        cout << (NN / 2);
        return 0;
    }

    for (int i = start; !v[i].visit; i = (i + 1) % NN) {
        v[i].visit = true;
        if (v[i].s != 0) {
            ans += v[i].s;
            if (iscnt) {
                if (cnt % 2 == 0) ans += cnt / 2;
                else           ans += (cnt + 1) / 2;
                cnt = 0;
                iscnt = false;
            }
        }
        else {
            cnt++;
            iscnt = true;
            continue;  
        }
    }

    if (iscnt) {
        if (cnt % 2 == 0) ans += cnt / 2;
        else             ans += (cnt + 1) / 2;
    }

    cout << ans;
    return 0;
}

//这里构建环的方法是在列表循环的最后再重新定位到开头的位置
//感觉有点屎山，后面再优化下
//这题有几个坑：如果所有的节点均为零，那就直接输出结果，不用再进行后面的判断了；continue容易直接跳过循环体中后面通用的内容；尽量不要在分支里continue，再循环体底部统一的进行i的更新