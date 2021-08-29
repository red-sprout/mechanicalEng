# T[i] = 3*T[i-2] + (2*T[i-4] + 2*T[i-6] ... + 2*T[0])
# i가 홀수이면 T[i] = 0
N = int(input())
T = [1,0,3]+[0 for _ in range(100)]
def DP(N):
    if N <= 2:
        return T[N]
    if N%2 != 0:
        return 0
    result = 0
    for i in range(0,N-1,2):
        if i == N-2:
            result += 3*DP(i)
        else:
            result += 2*DP(i)
    T[N] = result
    return T[N]
print(DP(N))
