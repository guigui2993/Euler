# -*- coding: utf-8 -*-
"""
Created on Mon Nov 20 08:15:02 2023

@author: lempereu
"""

lim = 200
l = [(0, 0, 1)]
for i in range(1, lim+1):
	n = i
	mul2, mul5 = 0, 0
	while n%5==0:
		n//=5
		mul5 += 1
	while n%2==0:
		n//=2
		mul2 += 1
	
	l.append((l[i-1][0] + mul2, l[i-1][1] + mul5, (l[i-1][2] * n)%100000)) #modulo for the last

print("done")



print(l[2])
print(l[10])

print(l[100])
#print(l[103])
#print(l[10000])


def f(n):
	if n <= 100:
		return l[n]
	
	r5 = f(n//5)
	r2 = f(n//2)
	r10 = f(n//10)
	r = (r2[0]+r5[0]-r10[0]+1, r2[1]+r5[1]-r10[1]+1, r2[2]*r5[2]//r10[2])
	#5*f(n//5) * 2*f(n//2) * (1) // (10*f(n//10)) # to do: 1,3,7,9
	#while r%10==0:
	#	r //= 10
	return r

a = 200
print("{}:".format(a))
print(f(a))

print(l[200])

exit()
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

