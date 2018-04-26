
import sys
import Euler


lim = 1000

for x in range(1,lim):
    for r in range(1,lim):
        if (x*(4*r-x)-1) %4 == 0:
            print(x,r)

print("-"*50)

sq = [i*i for i in range(5000)]

for a in range(1,lim):
    for r in range(1,lim):
        if 4*r*r-4*a-1 in sq:
            print(x,r)
