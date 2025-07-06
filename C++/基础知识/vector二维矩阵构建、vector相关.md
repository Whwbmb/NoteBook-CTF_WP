## vector二维矩阵实现

如果使用vector去构建二维矩阵，则可以采用这种一次性声明的方式：
```c++
vector<vector<int>> mat(n, vector<int>(m, default_value));
```

也可以使用下面的这种动态的方式：

```c++
int n, m;
cin >> n >> m;  

// Step 1：先构造“n 行”，每一行暂时是空 vector<int>：
vector<vector<int>> mat(n);
//或者是下面的这种方式：
vector<vector<int>> mat;
mat.resize(n);

// Step 2：给每一行再分配 m 列大小
for (int i = 0; i < n; ++i) {
    mat[i].resize(m);
}

// 如果想一开始就对所有元素赋默认值，也可以在 resize 中指定第二个参数：
for (int i = 0; i < n; ++i) {
    mat[i].resize(m, 0);  // 所有元素初始化为 0
}
```


## 关于二维矩阵的遍历：
在c++11即以上中：

```c++
for (int i = 0; i < n; ++i) {
    for (int &elem : mat[i]) {
        // elem 就是 mat[i][j]，这里 j 隐式地随 elem 变化
        cout << elem << ' ';
    }
    cout << '\n';
}

或是这种全部都一样的实现：
for (auto &row : mat) {
    for (auto &elem : row) {
        cout << elem << ' ';
    }
    cout << '\n';
}


```

**如果想要返回一个空的vector：**
```cpp
std::vector<int> f() {
    // 方法 1：显式构造
    return std::vector<int>();        // 空 vector
}

std::vector<int> g() {
    // 方法 2：列表初始化（C++11 起最简洁）
    return {};                        // 同样返回空 vector
}

std::vector<int> h() {
    // 方法 3：先声明空容器，再返回
    std::vector<int> ans;             // 默认构造就是空
    return ans;                       // Move Return Value Optimization
}
```