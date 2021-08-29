n,k = map(int,input().split())
dp = [[0]*(k+1) for i in range(n+1)]
w = [0]
v = [0]
for i in range(n):
    w_,v_ = map(int,input().split())
    w.append(w_)
    v.append(v_)
for i in range(1,n+1):
    for j in range(k,0,-1):
        if j-w[i] >= 0:
            dp[i][j] = max(dp[i-1][j],v[i]+dp[i-1][j-w[i]])
        else:
            dp[i][j] = dp[i-1][j]
print(dp[n][k])
