a=list(map(int,input().split()))
for i in range(len(a)):
    min_index = i
    for j in range(i,len(a)):
        if a[min_index] > a[j]:
            min_index = j
    tmp = a[min_index]
    a[min_index] = a[i]
    a[i] = tmp

for i in a:
    print(i,end=' ')
