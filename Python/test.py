# x=1
# s = "hello hello"

# print(s.index("lo"))          # 3
# print(s.index("lo", 4))       # 9
# print(s.index("he", 1))       # 6
# print(s.index(""))            # 0
# print("hello".index("he", 1))

#输入变量
a,b,c=map(int,input().split())
print(a,b,c,a+b)

# 输入列表（数组形式）
a=list(map(int,input().split()))
print(a)

# 输入二维列表
a=[]
n=int(input())
a=[list(map(int,input().split())) for _ in range(n)]
print(a)