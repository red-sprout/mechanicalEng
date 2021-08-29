memo = [0,1,1,1,2,2] + [0 for _ in range(100)]
def f(n):
    for i in range(6,n+1):
        memo[i] = memo[i-1]+memo[i-5]
    return memo[n]
n=int(input())
print(f(n))
