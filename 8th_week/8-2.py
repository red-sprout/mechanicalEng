<<<<<<< HEAD
N = int(input())
result = 0
s = [0]*(N+1)
def istrue(x):
    for i in range(1,x):
        if s[x]==s[i] or abs(s[x]-s[i])==abs(x-i):
            return False
    return True
def dfs(cnt):
    global result
    if cnt>N:
        result+=1
    else:
        for i in range(1,N+1):
            s[cnt] = i
            if istrue(cnt):
                dfs(cnt+1)
dfs(1)
print(result)
=======
N = int(input())
result = 0
s = [0]*(N+1)
def istrue(x):
    for i in range(1,x):
        if s[x]==s[i] or abs(s[x]-s[i])==abs(x-i):
            return False
    return True
def dfs(cnt):
    global result
    if cnt>N:
        result+=1
    else:
        for i in range(1,N+1):
            s[cnt] = i
            if istrue(cnt):
                dfs(cnt+1)
dfs(1)
print(result)
>>>>>>> 288e1950fe9402704d526ecb729f2141d73199c3
