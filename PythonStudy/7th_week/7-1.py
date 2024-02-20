def hanoi(n,frompole,topole,withpole):
    if n==1:
        print('Move no.{} disk : {} to {}'.format(n,frompole,topole))
    else:
        hanoi(n-1,frompole,withpole,topole)
        print('Move no.{} disk : {} to {}'.format(n,frompole,topole))
        hanoi(n-1,withpole,topole,frompole)
n = int(input())
hanoi(n,'A','B','C')
