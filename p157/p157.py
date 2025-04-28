"""
p157
1/a + 1/b = p/10 => 20 solutions
10**n * (a+b)/(a*b) = p <=> 10**n * (a+b) = p * a*b
10**n * a + 10**n * b - p*(a*b) = 0
ax² + bxy + cy² + dx + ey + f = 0
a = c = 0 and D = E = 10**n and B = -p
Bxy + Dx + Ey + F = 0
------
https://www.alpertron.com.ar/METHODS.HTM#SHyperb
Simple Hyperbolic case A = C = 0; B ≠ 0 , a hyperbola whose asymptotes are parallel to x and y axes
DE-BF = 10**(2*n) - 0 > 0

Let d1, d2, ..., dn be the set of divisors of DE - BF = 10**(2*n)

x = (d_i - E)/B = (d_i - 10**n)/(-p)
y = ((DE-BF)/d_i - D)/B = (10**(2*n) / d_i - 10**n)/(-p)

x = (10**n - d_i)/p
y = 10**n *(1- 10**n / d_i) / p
Issue ?

d_i < 10**n
ex: p = 7, d_i = {1, 2, 5, 10, 20, 50, 100} 10**(2*n) = 100
------
ex: p = 7

Solving the diophantine equation ax2 + bxy + cy2 + dx + ey +f = 0
(a, b, c, d, e, f)=(0, -7, 0, 10, 10, 0)
D=49
alpha = 70, beta = 70
49x = X + 70
49y = Y + 70
solving -7​XY = -34300:
Y(-7X) = -34300
i.e. Y(-X) = -4900
solution[0]: (2,5)
solution[1]: (5,2)
solution[2]: (0,0)
3 solutions
"""

import sys

lim = int(sys.argv[1])

n = 1
#for p in range(1, lim):

p = 7
dl = [1, 2, 4, 5, 10, 20, 25, 50, 100]
dl += [-1, -2, -4, -5, -10, -20, -25, -50, -100]
for d in dl:
    if (10**n - d) % p == 0:
        x = (10**n - d)//p
        y = (10**n) * (1 - (10**n)//d)//p
        print("{}\t{}".format(x, y))
