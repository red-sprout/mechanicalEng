def determine(s,d):
    tool=['+','-']
    arr = s.split(tool[-d])
    result = 0
    n=0
    for i,ele in enumerate(arr[0].split(tool[1-d])):
        if d == 0:
            if i == 0:
                result += int(ele)
            else:
                result -= int(ele)
        else:
            result += int(ele)
    for i in arr[1:]:
        for j,ele in enumerate(i.split(tool[1-d])):
            if d == 0:
                if j == 0:
                    result += int(ele)
                else:
                    result -= int(ele)
            else:
                result -= int(ele)
    return result

s = input()
print(determine(s,0),determine(s,1))
