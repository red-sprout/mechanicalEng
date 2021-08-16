N,B = map(int,input().split())
matrix = [list(map(int,input().split())) for _ in range(N)]

def power(m,b):
    if b == 1:
        return m
    tmp = power(m,b//2)
    tmp_square = multi(tmp,tmp)
    if b%2 == 0:
        return tmp_square
    elif b%2 == 1:
        return multi(tmp_square,m)


def multi(m_1,m_2):
    result = [[0]*N for _ in range(N)]
    for i in range(N):
        for j in range(N):
            for k in range(N):
                result[i][j] += m_1[i][k]*m_2[k][j]
                print(result)
    return result

answer = power(matrix,B)
for i in range(N):
    print(*answer[i])
