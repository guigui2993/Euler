# -*- coding: utf-8 -*-
"""
Created on Fri Nov 17 09:24:31 2023

@author: lempereu
"""

def fac(n):
	if n == 2:
		return 2
	return n*fac(n-1)

def lsb_nz(n, nbDig):
	exp = n.bit_length()*3//10+1
	zeros = 10**exp
	
	while exp > 0:
		while n%zeros == 0:
			n = n//zeros
		exp = exp // 2	
	
	while n%10 == 0:
		n = n//10
	
	return n%(10**nbDig)
	

print(fac(99)/fac(9))

(print(lsb_nz(1, 3)))
(print(lsb_nz(10, 3)))
(print(lsb_nz(77, 3)))
(print(lsb_nz(8320987112741390144276341183223364380754172606361245952449277696409600000000000000, 3)))

print("100:\n")
(print(lsb_nz(fac(100), 2)))

print("100:\n")
print(fac(100))

(print(lsb_nz(fac(99)//fac(9), 2)))
(print(lsb_nz(fac(9), 2)))

print("1000:\n")
(print(lsb_nz(fac(999), 2)))


f = 1
for i in range(11,100):
	if i%10==0:
		continue
	f *= i

print(f)

f = 1
for i in range(11,100):
	if i%10==0 or i%5==0:
		continue
	f *= i

print(f)

f = 1
for i in range(11,100):
	if i%10==0 or i%2==0:
		continue
	f *= i

print(f)


f_11_99 = 56
f_11_99_no5 = 76
f_11_99_no2 = 75

"""
	000 1
	00X 88
	0X0 88
	0XX 56
	X00 88
	X0X 9! 88**9
	XX0 56	
	XXX 56**9

"""
print("#"*100)

n = 1
for x in range(1, 10):
	n *= x
	
print(n)

print("#"*100)

n = 1
for x in range(1, 10):
	n *= (x*10)
	
print(n)

print("#"*100)

n = 1
for x in range(1, 10):
	for y in range(1, 10):
		n *= (10*x+y)
	
print(n)

print("#"*100)

n = 1
for x in range(1, 10):
	n *= (x*100)
	
print(n)

print("#"*100)

n = 1
for x in range(1, 10):
	for y in range(1, 10):
		n *= (100*x+y)
	
print(n)

print("#"*100)

n = 1
for x in range(1, 10):
	for y in range(1, 10):
		n *= (100*x+y*10)
	
print(n)

print("#"*100)

n = 1
for x in [1,2,3,4,6,7,8,9]: #range(1, 10):
	for y in range(1, 10):
		for z in range(1, 10):
			if z%5==0:
				continue
			n *= (100*x+y*10+z)
print(n)

n = 1
for x in [1,2,3,4,5,6,7,8,9]: #range(1, 10):
	for y in range(1, 10):
		for z in range(1, 10):
			if z%5==0:
				continue
			n *= (100*x+y*10+z)
print(n)
print(76**9)

n = 1
for x in [1,2,3,4,5,6,7,8,9]: #range(1, 10):
	for y in range(1, 10):
		for z in range(1, 10):
			for a in range(1, 10):
				if z%5==0:
					continue
				n *= (1000*a+100*x+y*10+z)
print(lsb_nz(n,2))
print(76**9)
""" 
	000 1
	00X 88
	0X0 88
	0XX 56
	X00 88
	X0X 9! 88**9
	XX0 56	
	XXX 56**9 => nope
	
	f_11_99 = 56
	f_11_99_no5 = 76
	f_11_99_no2 = 75
	
	X * f_11_99_no5
	[1,2,3,4,6,7,8,9] * X5
	
	XX5

	
"""



