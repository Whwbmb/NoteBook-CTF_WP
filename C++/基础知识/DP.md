# DP（Dynamic Programming 动态规划）

---

使用缓存（哈希表、集合或数组）保存计算结果，从而避免子问题重复计算的方法，就是「**动态规划算法**」

能够使用动态规划方法解决的问题必须满足以下三个特征：
- ***最优子结构性质***
  - 最优子结构：指的是一个问题的最优解包含其子问题的最优解。
- ***重叠子问题性质***
  - 重叠子问题性质：指的是在求解子问题的过程中，有大量的子问题是重复的，一个子问题在下一阶段的决策中可能会被多次用到。如果有大量重复的子问题，那么只需要对其求解一次，然后用表格将结果存储下来，以后使用时可以直接查询，不需要再次求解。
- ***无后效性***
  - 无后效性：指的是子问题的解（状态值）只与之前阶段有关，而与后面阶段无关。当前阶段的若干状态值一旦确定，就不再改变，不会再受到后续阶段决策的影响。

使用动态规划方法来解决问题的基本思路如下：

- 划分阶段：将原问题按顺序（时间顺序、空间顺序或其他顺序）分解为若干个相互联系的「阶段」。划分后的阶段⼀定是有序或可排序的，否则问题⽆法求解。
这里的「阶段」指的是⼦问题的求解过程。每个⼦问题的求解过程都构成⼀个「阶段」，在完成前⼀阶段的求解后才会进⾏后⼀阶段的求解。
- 定义状态：将和子问题相关的某些变量（位置、数量、体积、空间等等）作为一个「状态」表示出来。状态的选择要满⾜⽆后效性。
一个「状态」对应一个或多个子问题，所谓某个「状态」下的值，指的就是这个「状态」所对应的子问题的解。
- 状态转移：根据「上一阶段的状态」和「该状态下所能做出的决策」，推导出「下一阶段的状态」。或者说根据相邻两个阶段各个状态之间的关系，确定决策，然后推导出状态间的相互转移方式（即「状态转移方程」）。
- 初始条件和边界条件：根据问题描述、状态定义和状态转移方程，确定初始条件和边界条件。
- 最终结果：确定问题的求解目标，然后按照一定顺序求解每一个阶段的问题。最后根据状态转移方程的递推结果，确定最终结果。

## DP维度的选择：

在做动态规划（DP）时，“维度”本质上就是状态中需要记下来、用来区分子问题的参数个数。
如果一个子问题需要用一个变量（比如“考虑到第 i 个元素” 或 “当前背包容量为 j”）就能唯一描述，那就是一维 DP；
如果需要两个变量（比如“考虑到第 i 个元素” 且 “当前已用 j 的资源”）才行，那就需要二位 DP；

## 1. 线性DP


求最大子序列的长度：
```c++
int n = nums.length;
int res = 1;
int[] dp = new int[n];
for (int i = 0; i < n; i++) {
    dp[i] = 1;//存放当前的最大长度
    for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {//如果现在取到的这个数的值比之前取到的数大，则可以将这个数放到之前的那个数的结尾
            dp[i] = Math.max(dp[i], dp[j] + 1);//即原来的dp[]可以+1，但这里要取的是最大的那个dp[]
            res = Math.max(res, dp[i]);//仅仅只是将最大长度同步到结果变量中
        }
    }
}
```

