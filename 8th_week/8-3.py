n,m = map(int,input().split())
trees = list(map(int,input().split()))
left,right = 1,max(trees)
answer = 0
while left <= right:
    mid = (left+right)//2
    total = 0
    for tree in trees:
        remain = tree-mid
        if remain > 0:
            total += remain         
    if total >= m:
        left = mid+1
        answer = max(answer,mid)
    else:
        right = mid-1
print(answer) 
