def f1(i, j, t, n):
    cent = (n//2, n//2)
    i -= cent[0]; j-= cent[1]
    i = abs(i); j = abs(j)

    ans = -1
    if i == 0 and j == 0:
        ans = 1
    elif i == 0 or j == 0:
        if i+j == t:
            ans = 1
        elif i+j < t:
            if i == n//2 or j == n//2:
                ans = 3
            else:
                ans = 2
        else:
            ans = 0
    else:
        if i+j == t:
            ans = 2
        elif i+j < t:
            if i == n//2  and j == n//2:
                ans = 2
            elif i == n//2 or j == n//2:
                ans = 1
            else:
                ans = 0
        else:
            ans = 0
    
    # print(ans, t-1-(i+j), t-1, i+j)
    ans += max(t-1-(i+j), 0)*4
    if i!= 0 and j != 0 and (t-1) >= (i+j):
        ans += 4
    # print(ans)
    return ans


n = int(input())
p = int(input())
for h in range(p):
    i, j, t, h = map(int, input().strip().split())
    a = f1(i, j, t, n)

    if a >= h: print("YES") 
    else: print("NO")









