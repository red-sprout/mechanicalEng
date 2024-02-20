# x_joint = a1*cos(theta)
# y_joint = a1*sin(theta)
import math

class angle:
    def __init__(self,a1,a2,x,y):
        self.a1 = a1
        self.a2 = a2
        self.x = x
        self.y = y
    def atan2(self):
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
    def t1(self):
        b = self.x**2 + self.y**2 + self.a1**2 - self.a2**2
        c = 2*a1 * math.sqrt(x**2+y**2)
        return math.acos(b/c)

class tool(angle):
    def __init__(self,a1,a2,x,y):
        super().__init__(a1,a2,x,y)
    def case1(self):
        return self.atan2() + self.t1()
    def case2(self):
        return self.atan2() - self.t1()
    def x_joint(self,theta):
        return self.a1*math.cos(theta)
    def y_joint(self,theta):
        return self.a1*math.sin(theta)

class IK(tool):
    def __init__(self,a1,a2,x,y):
        super().__init__(a1,a2,x,y)
    def joint(self):
        #예외처리
        try:
            print([self.x_joint(self.case1()),self.y_joint(self.case1())])
            print([self.x_joint(self.case2()),self.y_joint(self.case2())])
        except:
            print('Impossible')

a1,a2,x,y = map(int,input().split())
Robot1 = IK(a1,a2,x,y)
Robot1.joint()
