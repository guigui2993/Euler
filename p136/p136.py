# problem 136
"""
x, y, z = x, x-r, x-2*r
x**2 - y**2-z**2 = x**2-

"""


l =[0]*100
lim = 1000
nmax = 0

for a in range(1,lim//4): # n = 4*a
    n = 4*a

    if a%4 == 2:
        continue

    if a%4 == 0:
        if not Euler.isprime(a//4) and a != 4:
            continue

        if a == 8:
            continue

        # One solution

    if a%4 == 3 or a%4 == 1:
        if not Euler.isprime(a):
            continue

        # One solution



for a in range(1,(lim+1)//4): # n = 4*i -1
    n = 4*a-1

    fact = Euler.factorization(a)
    if len(fact) > 1:
        continue
    pl = list(fact)
    p, e = pl[0], fact[pl[0]]

    if e > 1: # need to check !!!!!
        continue

    # Only one solution
    r = a
    d = 2*a-1
    x = 1 # !!!!!!!!!!!!!
    print(x,r)


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

