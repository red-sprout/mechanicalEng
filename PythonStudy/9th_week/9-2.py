J = [[0,0,0]]
RGB = [[0,0,0]]
N = int(input())
for i in range(N):
    RGB.append(list(map(int,input().split())))
for i in range(1,N+1):
    if i == 1:
        J.append(RGB[i])
    else:
        J.append([0,0,0])
        for j in range(3):
            J[i][j] = min(J[i-1][j-1]+RGB[i][j],J[i-1][j-2]+RGB[i][j])
print(min(J[N]))
