# -*- coding: utf-8 -*-
"""
Created on Wed Mar  1 08:52:49 2017

@author: lempereu
P141
"""

# n = d*q+r
# Brute Force
# may be optimized: d start at sqrt(n)
import math

c = 0
lim = 1000
for n in range(1,lim):
    for d in range(math.floor(math.sqrt(n)),n+1):
        r = n%d
        
        if r == 0:
            continue
        q = n//d

        if d>q:
            if d/q == q/r or d/q == r/q:
                
                c += 1
                if q < r:
                    print("yolo")
                    print(n,d,q,r)
                break
        """
        if q>d:
            if q/d == d/r:
                print(n,d,q,r)
                c += 1
                break
       """     
        
    #print("-"*10)
print(c)