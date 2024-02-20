a=list(map(int,input().split()))
for i in range(1,len(a)):
    for j in range(i,0,-1):
        if a[j] < a[j-1]:
            tmp = a[j]
            a[j] = a[j-1]
            a[j-1] = tmp

for i in a:
    print(i,end=' ')
