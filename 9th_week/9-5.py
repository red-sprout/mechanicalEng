N = int(input())
A = list(map(int,input().split()))
result = [0 for _ in range(N)]
for i in range(N):
    min_value = 0
    for j in range(i):
        if A[i] > A[j]:
            min_value = max(min_value,result[j])
    result[i] = min_value+1
print(max(result))
