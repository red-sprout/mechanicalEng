import math

def atan2(y,x):
    if x>0:
        return math.atan(y/x)
    elif x<0 and y>=0:
        return math.atan(y/x)+math.pi
    elif x<0 and y<0:
        return math.atan(y/x)-math.pi
    elif x==0 and y>0:
        return math.pi/2
    elif x==0 and y<0:
        return -math.pi/2

def t1(x,y,a1,a2):
    b = x**2+y**2+a1**2-a2**2
    c = 2*a1*math.sqrt(x**2+y**2)
    if not (x==0 and y==0):
        return math.acos(b/c)

def d(x,y):
    return math.sqrt(x**2+y**2)

def IK(x,y,a1,a2):
    if (x==0 and y==0):
        print('Impossible')
    elif d(x,y)>(a1+a2):
        print('Impossible')
    elif d(x,y)<(max(a1,a2)-max(a1,a2)):    # abs(a1-a2) 도 가능
        print('Impossible')
    else:
        elbow1 = [a1*math.cos(atan2(y,x)+t1(x,y,a1,a2)),a1*math.sin(atan2(y,x)+t1(x,y,a1,a2))]
        elbow2 = [a1*math.cos(atan2(y,x)-t1(x,y,a1,a2)),a1*math.sin(atan2(y,x)-t1(x,y,a1,a2))]
        print(elbow1)
        print(elbow2)

a1,a2,x,y = map(int,input().split())
IK(x,y,a1,a2)
