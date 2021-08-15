def hansu(N):
    count=0
    for num in range(1,N+1):
        if num < 100:
            count += 1
            continue
        num_list = list(map(int,str(num)))
        d = num_list[1]-num_list[0]
        for i in range(1,len(num_list)):
            if num_list[i]-num_list[i-1] != d:
                break
            elif i == len(num_list)-1:
                count += 1
    return count

N = int(input())
print(hansu(N))
