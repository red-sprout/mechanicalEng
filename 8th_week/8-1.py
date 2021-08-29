N = int(input())
def bs():
    start = 0
    end = N
    while start <= end:
        mid = (start+end)//2
        if mid*mid == N:
            return mid
        elif mid*mid > N:
            end = mid-1
        else:
            start = mid+1
    return -1
print(bs())
