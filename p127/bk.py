"""
Try for p 127

c = p**2
"""

import sys
sys.path.append('..')
import Euler
s = 0

lim = int(sys.argv[1])+1

for n in range(1,lim):
    #print(n,Euler.factorization(n))
    facts = Euler.factorization(n)
    ab = 1
    for i in facts:
        #print(i)
        ab *= i**(facts[i]-1)
    #s += ab

    #a+b < ab
    if ab < 6:
        continue
    
    #s += 1





print(s)
