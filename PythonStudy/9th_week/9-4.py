# T[i] = 2*T[i-1] + 3*T[i-2] + (2*T[i-3] + 2*T[i-4] ... + 2*T[0])
N = int(input())
T = [[0,0] for _ in range(100)]
# T[i][0] : 실제 값
# T[i][1] : 2가 곱해진 T[i-3]+...+T[0] 부분 합
# T[i][0] = 2*T[i-1][0] + 3*T[i-2][0] + 2*T[i][1]
T[0][0] = 0;
T[1][0] = 2;
T[2][0] = 7;
T[2][1] = 1;
def DP(N):
    if N <= 2:
        return T[N][0]
    for i in range(3,N+1):
        T[i][1] = T[i-1][1]+T[i-3][0]
        T[i][0] = 2*T[i-1][0] + 3*T[i-2][0] + 2*T[i][1]
    return T[N][0]
print(DP(N))
