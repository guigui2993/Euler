# problem 136
"""
x, y, z = x, x-r, x-2*r
x**2 - y**2-z**2 = x**2-

"""


l =[0]*100
lim = 1000
nmax = 0
for r in range(1,lim):
    for x in range(2*r,7*r):
        n = (7*r-x)*(x+r)
        nmax = max(nmax,n)

        if n > 0 and n < 100:
            l[n] += 1

s = 0
for i in range(1,100):
    if l[i] == 1:
        s += 1

print(sum(l))
print(s)

