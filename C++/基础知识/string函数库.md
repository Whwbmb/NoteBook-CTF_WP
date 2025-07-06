# string （C++17/20 常用接口）

---

## 1.  构造与初始化

```cpp
string s1;                     // 空
string s2("hello");            // C-风格字面量
string s3(5, 'A');             // "AAAAA"
string s4 = s2.substr(1, 3);   // "ell子串"
```

* **字面量后缀**：`"abc"s`（C++14，需要 `using namespace std::string_literals;`）。

---

## 2.  大小与容量

| 方法                    | 说明            |
| --------------------- | ------------- |
| `size()` / `length()` | 当前长度          |
| `empty()`             | 是否为空          |
| `resize(n, ch)`       | 重新设长，不足填 `ch` |
| `reserve(n)`          | 预留容量          |
| `capacity()`          | 已分配容量         |
| `shrink_to_fit()`     | 释放多余容量        |

---

## 3.  访问元素

```cpp
char c1 = s[i];       // 不检查越界（UB）
char c2 = s.at(i);    // 越界抛异常
char& first = s.front();
char  last  = s.back();
```

* C++17 起 `data()` 返回可写指针，与 `c_str()` 等价但非 const。

---

## 4.  拼接与插入

```cpp
s += "world";
string t = s + "!";
s.append("012", 2);        // 追加前 2 个字符 -> "01"
s.insert(2, "xxx");        // 下标 2 处插入
```

---

## 5.  删除与清空

```cpp
s.erase(2, 3);             // 从下标 2 起删 3 个
s.pop_back();
s.clear();
```

---

## 6.  查找与替换

```cpp
auto pos = s.find("abc");          // 找不到 → npos
auto rpos = s.rfind('a');

s.replace(pos, 3, "XYZ");          // 把 [pos,pos+3) 替换
s.starts_with("http");  // C++20
s.ends_with(".png");    // C++20
```

---

## 7.  子串与比较

```cpp
string sub = s.substr(5);     // [5, end)
int cmp = s.compare(t);            // <0, =0, >0
bool eq  = (s == t);               // 运算符重载
```

---

## 8.  数值 ↔ 字符串转换

| 字符串 → 数值                      | 数值 → 字符串                            |
| ----------------------------- | ----------------------------------- |
| `stoi / stol / stoll`         | `to_string`                         |
| `stof / stod / stold`         | `std::format("{} {}", a,b)` (C++20) |
| `from_chars` (C++17，无 locale) | `to_chars` (C++17，无分配)              |

---

## 9.  与 C 字符串互操作

```cpp
const char* p = s.c_str();   // 以 '\0' 结尾，安全读
char*       q = s.data();    // C++17 起可写
```

* 可直接传入 `printf`, `strcpy`, `fwrite` 等 C API。

---

## 10.  I/O

```cpp
std::cin  >> s;          // 读到空白
std::getline(std::cin,s);// 读整行
std::cout << s << '\n';
```

---

## 11  迭代器与算法

```cpp
std::sort(s.begin(), s.end());
for (char ch : s) { … }           // range-for
```

* 支持 `begin()/end()`，可用所有 `<algorithm>` 通用算法。

---

## 12  其他常用类型

| 类型                                                        | 说明                      |
| --------------------------------------------------------- | ----------------------- |
| `std::string_view`                                        | 轻量只读视图，零拷贝切片            |
| `std::u8string` (UTF-8)，`std::u16string`，`std::u32string` | 宽字符编码                   |
| `std::wstring`                                            | 平台相关宽字符（Windows UTF-16） |

---


`字符串反转：`
```cpp
#include <algorithm>
#include <iterator>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @param n int整型 
     * @return string字符串
     */
    string trans(string s, int n) {
        // write code here
        if(n==0)return s;
        for(int i=0;i<n;i++){
            if(s[i]>='a'&&s[i]<='z')s[i]+='A'-'a';
            else if(s[i]>='A'&&s[i]<='Z')s[i]+='a'-'A';
            
        }
        reverse(s.begin(), s.end());
        for(int i=0;i<n;i++){
            int j=i;
            while(1){
                if(s[j]!=' '&&j<n)j++;
                else break;
            }
            reverse(s.begin()+i,s.begin()+j);
            i=j;
        }
        return s;
    }
};
```
**求字符串数组的最大公共前缀：**
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        //空字符串数组
        if(n == 0) 
            return "";
        //遍历第一个字符串的长度
        for(int i = 0; i < strs[0].length(); i++){ 
            char temp = strs[0][i]; 
            //遍历后续的字符串
            for(int j = 1; j < n; j++) 
                //比较每个字符串该位置是否和第一个相同
                if(i == strs[j].length() || strs[j][i] != temp) 
                    //不相同则结束
                    return strs[0].substr(0, i); 
        }
        //后续字符串有整个字一个字符串的前缀
        return strs[0]; 
    }
};
```

