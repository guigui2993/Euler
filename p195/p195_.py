
"""
https://www.dcode.fr/divisors-list-number

c*c = a*a - a*b + b*b

y = (x +/- sqrt(x²4*x²+4*c²))/2
y = (x +/- (4*c*c-3*x*x)**0.5)/2
b = (a +/- (4*c*c-3*a*a)**0.5)/2

4*c*c-3*x*x = t*t

4*c*c - 3*a*a - t*t = 0
4*c*c - t*t - 3*a*a = 0
A = 4, C = -1, F = -3*a*a
B²-4AC = 0-4*4*-1 = 16 = 4², k = 4
x = c, y = t

ex:
a = 3, b = 8, c = 7
t = 13

u multiple of -4AF = -4*4*-3*a*a = 48*a*a = 432


case: a = 14
6, 16, 6 and, 8, 16, 6
"""

def listDiv(a):
	"""
	if a%2==0:
		u%8=0
	else
		u%8=1
	"""
	lst = []
	n= 48*a*a
	for i in range(1,n):
		if n%i == 0:
			lst.append(i)
	return lst

ul = [1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 27, 36, 48, 54, 72, 108, 144, 216, 432]
#ul = [1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 27, 32, 36, 48, 54, 64, 72, 96, 108, 144, 192, 216, 288, 432, 576, 864, 1728]
a, b, c = 6, 8, 7
print(a*a - a*b + b*b)
print(c*c)

print()
print(4*c*c - 3*a*a)

dic = {}
cnt = 0
lim = 100 #1053779
a_max = lim
a_min = 1

ccc = 0

while ccc < 20:
	a = (a_max + a_min)//2
	
	r = ((a**3-2*a)/a)**(3/2)
	r_p1 = (((a+1)**3-2*a-2)/(a+1))**(3/2)
	
	

	print("a", a)
	ccc += 1
	if r < lim and r_p1 > lim:
		print("Success: ", a)
		break
	elif r > lim:
		a_max = a
	else:
		a_min = a



for a in range(1,200):
	ul = listDiv(a)

	# u > 12*a
	for u in ul:
		#if u <= 12*a:
		#	continue
		#u *= -1
		t = (u-(16*3*a*a)/u)/8
		c = (u-4*t)/8

		if abs(round(t)-t)>0.05 and abs(round(c)-c)>0.05:
			continue
		t = (u-(16*3*a*a)//u)//8
		c = (u-4*t)//8
		
		if (a + t)%2!=0 or (a + t)<1:
			continue
		
		#print(u, c, t)
		b = (a + t)//2
		#b = (a + (4*c*c-3*a*a)**0.5)/2
		
		s = (a+b+c)/2
		r = (s-a)*(s-b)*(s-c)/s
		
		if r < lim*lim:
			cnt += 1
			
			b, a = max(b, a), min(b, a)
			c, a = max(c, a), min(c, a)
			b, c = max(b, c), min(b, c)
			if a != b:
				dic[(b, c, a)] = 0
				print(b, c, a)

		"""		
		b = (a - (4*c*c-3*a*a)**0.5)/2
		print(b, c, a)
		print()
		
		print("#"*10)
		print(a + u/4," > ",4*c)
		print(u > 16*c-4*a)
		print(8*t+4*a > u)
		
		#print(16*c, u + 48*a*a/u)
		#print(c,(u*u+48*a*a)/(16*u))
		#print(u, (16*a + (16*16*a*a-4*48*a*a)**0.5)/2)
		#print(u, (16*a - (16*16*a*a-4*48*a*a)**0.5)/2)
		#print("#"*10)
		
		#print(u, (16*a - (16*16*a*a-4*48*a*a)**0.5)/2)
		"""

print(cnt)
print(len(dic))

"""
4t = u-8c
2u-16c =  (u-(16*3*a*a)/u)
48aa/u = 16c-u
48aa = 16cu -uu
16c = u + 48aa/u

16cu = u² + 48aa
c>a

c = (u*u+48a*a)/(16*u)


(u*u+48a*a)/(16*u) > a
(u*u+48a*a) > 16*a*u
(u*u - 16*a*u + 48*a*a) > 0 


16a > u +48aa/u
u +48aa/u -16 a < 0
uu -16au + 48 aa < 0 (si u>0)


b = (a + t)/2
2*b - a = t = (u-8*c)/4
2*b = a + (u-8*c)/4

b = a/2 + (u-8*c)/8
b > c
a/2 + (u-8*c)/8 > c
a/2 + u/8 > 2*c
a + u/4 > 4*c
u/4 > 4*c-a
u > 16*c-4*a
u > 2*(u-4*t)-4*a
u > 2*u-8*t-4*a
8*t+4*a > u
u-(16*3*a*a)/u + 4*a > u


--
	t = (u-(16*3*a*a)/u)/8
	c = (u-4*t)/8
--
a + u/4 > 4*a
u/4 > 3*a
u > 12*a !!!!

x = (-b +/- (b*b-4*a*c)**0.5)/2/a

u = (16*a +/- (16*16*a*a-4*48*a*a)**0.5)/2
u = (16*a +/- 8*a)/2
u = 8*a +/- 4*a
u = [4*a, 12*a] ; u <12 or >36

ans:
c	t
7	-13
3	-3
3	3	(36)
7	13	(108)
"""

"""
c^2 = a^2 + b^2 - 2*a*b*cos(60°)
c^2 = a^2 - a*b + b^2

b = (a +/- (a**2-4*(a**2-c**2))**0.5)/2
b = (a +/- (4*c**2-3*a**2))**0.5)/2

--
4*c**2-3*a**2 = n**2

(2*c)**2 = n**2 + 3*a**2 (x² + 3 y²) d = 3

solution: n = 6, a = 6

x = ((6+6*(3)**0.5)**n + (6-6*(3)**0.5)**n)/2
y = ((6+6*(3)**0.5)**n - (6-6*(3)**0.5)**n)/2


-------------------------------

(2*c)**2 = x**2 + 3*a**2
x**2 + 3*a**2 - (2*c)**2 = 0
A 1, B 0, C 3, D 0, E 0, F -c²
a = sqrt(-4*3*(x²-4c²))/6
a = sqrt(12*(4c²-x²))/6
a = sqrt(3*(4c²-x²))/3

-------------------------------

Xn+1 = (r2 - ACs2)Xn - Cs(2r+Bs)Yn - CDs2 - Ers    (40)

Yn+1 = As(2r+Bs)Xn + [r2 + 2Brs + (B2-AC)s2]Yn + Ds(r+Bs) - AEs2    (41)

r² + Brs + ACs² = r² + 3s² = 1

x_n* = 

-----------------------------------------------------------------------------------

# Online Python - IDE, Editor, Compiler, Interpreter

""
LIM = 11
for a in range(1, LIM):
    for b in range(1, LIM):
        for c in range(1, LIM):
            if c*c == a*a + b*b - a*b:
                print(a,b,c)

x = (4/3*7*7)**(1/2)

print(-x/2)
""


for n in range(-20,20):
    x0, y0 = 11, 11
    x = ((x0+y0*(3)**0.5)**n + (x0-y0*(3)**0.5)**n)/2
    y = ((x0+y0*(3)**0.5)**n - (x0-y0*(3)**0.5)**n)/(2*(2)**0.5)
    
    print(x, y, (x*x+3*y*y)**0.5)
	
"""