import math
def f(x):
    return x*math.exp(-x)

def interval(a,b):
    m = f(a)-0.2
    n = f(b)-0.2
    if m*n<=0:
        print('확실합니다.')
    else:
        print('불확실합니다.')

a,b=map(float,input().split())
interval(a,b)
