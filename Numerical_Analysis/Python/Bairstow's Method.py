import math
#다항식 차수 입력(5차 방정식이면 5)
#각 다항식 계수 입력(차수는 내림차순)
def bairstow(n,a,root):
    if n==1:
        if a[1]==0:
            return
        r1=round(-a[0]/a[1],4)
        root.append(str(r1))
        return
    elif n==2:
        if a[2]==0:
            a.pop(2)
            return bairstow(1,a,root)
        D=a[1]*a[1]-4*a[0]*a[2]
        if D>=0:
            R1=round((-a[1]+math.sqrt(D))/2,4)
            R2=round((-a[1]-math.sqrt(D))/2,4)
            root.append(str(R1))
            root.append(str(R2))
            return
        else:
            r1=round(-a[1]/2,4)
            i1=round(math.sqrt(abs(D))/2,4)
            r2=r1
            i2=i1
            R1="{}+{}i".format(r1,i1)
            R2="{}-{}i".format(r2,i2)
            root.append(R1)
            root.append(R2)
            return
    ea=1
    es=0.5
    ier=0
    r,s=-a[n-1]/a[n],-a[n-2]/a[n]
    b=[0 for _ in range(n+1)]
    c=[0 for _ in range(n+1)]
    while ea>es or ier<100:
        ier=ier+1
        for i in range(n,-1,-1):
            if i==n:
                b[i]=a[i]
                c[i]=b[i]
            elif i==n-1:
                b[i]=a[i]+r*b[i+1]
                c[i]=b[i]+r*c[i+1]
            else:
                b[i]=a[i]+r*b[i+1]+s*b[i+2]
                c[i]=b[i]+r*c[i+1]+s*c[i+2]
        det=c[1]*c[3]-c[2]*c[2]
        if det!=0:
            dr=(b[1]*c[2]-b[0]*c[3])/det
            ds=(b[0]*c[2]-b[1]*c[1])/det
            r=r+dr
            s=s+ds
            if r*s!=0:
                ea=max(abs(dr/r)*100,abs(ds/s)*100)
        else:
            r=r+1
            s=s+1
    sol2=[-s,-r,1]
    bairstow(2,sol2,root)
    b.pop(0)
    b.pop(0)
    return bairstow(n-2,b,root)

n=int(input())                      #다항식 차수 입력(5차 방정식이면 5)
a=list(map(float,input().split()))  #각 다항식 계수 입력(차수는 내림차순)
root=[]
bairstow(n,a,root)
for i,j in enumerate(root):
    print("x%d ="%(i+1),j)
