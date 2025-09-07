row,col = map(int,input().split())
matrix=[[0 for _ in range(row)] for _ in range(col)]
for i in range(row):
    for j in range(col):
        print(" ".join(f"{x:4}"for x in row))