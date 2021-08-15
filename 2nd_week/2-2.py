n=int(input())
left=1
right=1
result=0
for i in range(n+1):
    if i==0 or i==1:
        result=1
        continue
    result=left+right
    right=left
    left=result
print(result)
