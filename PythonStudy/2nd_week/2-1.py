year=int(input())
if year%400==0:
    print('윤년입니다.')
elif year%4==0 and year%100!=0:
    print('윤년입니다.')
else:
    print('윤년이 아닙니다.')
