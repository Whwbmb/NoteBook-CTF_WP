## gcd

## 1. 标准库 `std::gcd`（C++17 起）

```cpp
#include <numeric>  // std::gcd, std::lcm (C++17)
#include <iostream>

int main() {
    int a = 42, b = 56;
    std::cout << "gcd(42,56) = " << std::gcd(a, b) << "\n";  // 输出 14
    return 0;
}
```

* 定义在 `<numeric>` 中，自 C++17 起可用。
* 支持整型（signed/unsigned）以及任意可做取模运算的整数类型。
* 对负数的处理：`std::gcd(-a, b)` 会返回非负结果。

```cpp
long long x = -15, y = 20;
auto g = std::gcd(x, y);  // 5
```

---

## 2. 标准库 `std::lcm`（C++17 起）

利用 gcd 快速计算最小公倍数：

```cpp
#include <numeric>
#include <iostream>

int main() {
    int a = 6, b = 8;
    std::cout << "lcm(6,8) = " << std::lcm(a, b) << "\n";  // 输出 24
}
```

* `lcm(a,b) = |a / gcd(a,b) * b|`，并由标准库直接提供。

---

## 3. GNU 扩展 `__gcd`（GCC/Clang）

在未开启 C++17 或需要兼容旧编译器时，可使用 GCC/Clang 提供的内建函数：

```cpp
#include <algorithm>   // 部分环境可不引入
#include <iostream>

int main() {
    int a = 27, b = 36;
    std::cout << "__gcd(27,36) = " << __gcd(a, b) << "\n";  // 输出 9
}
```

* 定义在 `<algorithm>` 或由编译器隐式提供。
* 仅限 GNU 系列编译器，不具备移植性。

---

## 4. 手写欧几里得算法

### 迭代版本

```cpp
template<typename T>
T gcd_iter(T a, T b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        T t = a % b;
        a = b;
        b = t;
    }
    return a;
}
```

### 递归版本

```cpp
template<typename T>
T gcd_rec(T a, T b) {
    if (b == 0) return a < 0 ? -a : a;
    return gcd_rec(b, a % b);
}
```

两者时间复杂度均为 O(log min(a,b))。

---

## 5. 拓展：扩展欧几里得算法（Extended GCD）

除了最大公约数，还能求出满足 `a·x + b·y = gcd(a,b)` 的整数解 `(x, y)`：

```cpp
#include <tuple>

template<typename T>
std::tuple<T, T, T> ext_gcd(T a, T b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = ext_gcd(b, a % b);
    T x = y1;
    T y = x1 - (a / b) * y1;
    return {g, x, y};
}

int main() {
    auto [g, x, y] = ext_gcd(30, 20);
    // g = 10, 且 30*x + 20*y == 10
}
```

扩展欧几里得常用于：

* 求解模逆元：`inv = x mod m` （当 gcd(a,m)=1 时）。
* 解一次同余方程。

---

## 6. 注意事项

1. **类型安全**

   * `std::gcd` 模板会根据参数类型推导返回类型，尽量避免混用带符号和不带符号类型，或在必要时显式转换。
2. **负数**

   * 标准实现会保证返回值非负；自写版本需手动取绝对值。
3. **零处理**

   * `gcd(0,0)` 在数学上未定义，但标准实现通常返回 0；`gcd(a,0)=|a|`。

