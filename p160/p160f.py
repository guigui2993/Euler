# -*- coding: utf-8 -*-
"""
Created on Mon Nov 20 08:15:02 2023

@author: lempereu
"""

#9109376
n = 1
n2 = 0
for i in range(1, 100000):
	if i%5==0:
		continue
	n2+=i%2
	n *= i
	#n%= 10000000
print(n)
exit(0)

#390625
n = 1
for i in range(1, 100000):
	if i%10!=5:
		continue
	n *= i
	n%= 10000000
print(n)

lim = 100000
l = [1]*(lim+1)
for i in range(1, lim+1):
	n = i * l[i-1]
	while n%10==0:
		n //=10
	l[i] = n%100000

print("done")

def f(n):
	if n <= 100000:
		return l[n]
	if n % 100000 != 0:
		print("issue")
		return 0
	exp = n//100000
	r = ((9376**exp)%100000) * ((90625**exp)%100000) * f(n//10)
	while r%10==0:
		r //= 10
	return r

lim = 200000
print("f: {}".format(lim))
print(f(lim))
	
"""
for i in l:
	print(i)"""

n = 1
for i in range(1, lim):
	n*=i
	while n%10==0:
		n //=10
	n%= 100000
print("real:")
print(n)


n = 1
lim = 100000
for i in range(1, lim):
	if i%10==0:
		continue
	n*=i
	while n%10==0:
		n //=10
	n%= 100000
print("real-5-0:")
print(n)
print("-"*20)
m = [9109376*90625,
	 49109376*90625,
	 749109376*90625,
	 8749109376*90625,
	 98749109376*90625,
	 10,
	 9109376*390625,
	 49109376*390625,
	 49109376*7390625,
	 1749109376*177390625,
	 71749109376*8177390625,
	 871749109376*68177390625,
	 9871749109376*368177390625,
	 1749109376*8177390625,
	 71749109376*8177390625,
	 1749109376*58177390625,
	 71749109376*58177390625,
	 23749109376*58177390625,
	 
	 ]

for i in m:
	while i%10==0:
		i//=10
	print(i%100000)
	
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 20 08:15:02 2023

@author: lempereu
"""

lim = 10000
l = [1]*(lim+1)
for i in range(1, lim+1):
	n = i * l[i-1]
	while n%10==0:
		n //=10
	l[i] = n#%100000000

print("done")

def f(n):
	if n <= 100:
		return l[n]
	r = 5*f(n//5) * 2*f(n//2) * (1) // (10*f(n//10)) # to do: 1,3,7,9
	while r%10==0:
		r //= 10
	return r

lim = 1000
print("f: {}".format(lim))
print(f(lim))

n = 1
for i in range(1, lim):
	n *= i
	while n%10==0:
		n //= 10
	n %= 1000000000
print("real:")
print(n)

#print(l[40000])
#print(l[100000])

print("-"*20)

def fac(n):
	r = 1
	for i in range(1,n+1):
		r *= i
	return r

n5 = 1
for i in range(1, 101):
	if i%5 == 0:
		n5 *= i
print(n5)

n2_5 = 1
for i in range(1, 101):
	if i%5 == 0 or i%2 ==0:
		n2_5 *= i
print(n2_5)

o5 = (5**20)*fac(20)
print(o5)

nn5 = 1
for i in range(1, 101):
	if i%5 != 0:
		nn5 *= i
print(nn5)

nn2_5 = 1
for i in range(1, 101):
	if i%5 != 0 and i%2!=0:
		nn2_5 *= i
print(nn2_5)

n2 = 1
for i in range(1, 101):
	if i%2 == 0:
		n2 *= i
print(n2)

o2 = (2**50)*fac(50)
print(o2)

n10 = 1
for i in range(1, 101):
	if i%10 == 0:
		n10 *= i
print(n10)

o10 = (10**10)*fac(10)
print(o10)


print(n5*nn5)
print(fac(100))
print(n2*n5*nn2_5//n10)
print(o2*o5*nn2_5//o10)

print("@"*20)
lim = 1000
print(fac(lim))

nn2_5 = 1
for i in range(1, lim+1):
	if i%5 != 0 and i%2!=0:
		nn2_5 *= i
#print(nn2_5)

print((2**(lim//2))*fac(lim//2) * (5**(lim//5))*fac(lim//5)*nn2_5//((10**(lim//10))*fac(lim//10)))
print("#"*50)
nn2_5 = 1
lim = 100
for i in range(1, lim):
	if i%5 != 0 and i%2!=0:
		nn2_5 *= i
	"""
	if i%10==0:
		print(i) 
		print(nn2_5)
		print()
	"""
print(nn2_5)
print()


