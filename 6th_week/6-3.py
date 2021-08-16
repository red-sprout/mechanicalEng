num = list(map(int,input().split()))
num.sort()
result = 0
left, right = 0, len(num)-1

while left<right:
    if num[left]<1 and num[left+1]<1:
        result += num[left]*num[left+1]
        left += 2
    else:
        break

while right>0:
    if num[right]>1 and num[right-1]>1:
        result += num[right]*num[right-1]
        right -= 2
    else:
        break

while left<=right:
    result += num[right]
    right -= 1

print(result)
