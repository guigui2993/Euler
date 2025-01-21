
N = 100
l = []

"""
y²-c² = 3*x
y²-4*x = n²

4*r²*(y+c) = x*(y-c)

y>c
c>y-sq(3)*N

"""
for y in range(1,N):
	for c in range(max(1,int(y-3**(1/2)*N)+1,(y//2)+1),y): # to check !!!
		if (y*y-c*c)%3 == 0:
			x = (y*y-c*c)//3
			if (int((y*y-4*x)**(1/2)))**2 == y*y-4*x:
				#print(x, y, c, (y*y-4*x)**(1/2))
				a_p_b = int((y*y)**(1/2))
				a_m_b = int((y*y-4*x)**(1/2))
				a = (a_p_b + a_m_b)//2
				b = (a_p_b - a_m_b)//2
				l.append((a, b, c, x, y))
		"""
			for x in range(1,N): # max(a,b)
				if (a+b+c)*(b+c-a) == 3*b*c:
					s = (a+b+c)/2
					r = ((s-a)*(s-b)*(s-c)/s)**(1/2)
					if r < 100:
						l.append((max(a,b),min(a,b),c))
		"""

print(l)
print(len(l))


"""

print("Hello world")

N = 55

k_s = {32: (9,7)}

for i in range(1,N):
    for j in range(1,N):
        k = i*i-j*j
        if k > 0 and k <= 100 and i-j >= 2:
            k_s[k] = (i,j)

print(k_s)
print(len(k_s))

--
r = ((s-a)(s-b)(s-c)/s)**(1/2)
r² = ((-a+b+c)(a-b+c)(a+b-c)/4/(a+b+c))
s = (a+b+c)/2

c² = a² + b² - 2*a*b*cos(60)
c*c = a*a + b*b - a*b = (a-b)²+a*b
c² - (a-b)² = a*b
(c-(a-b))*(c+(a-b)) = a*b
(b+c-a))*(a+c-b) = a*b

r² = a*b*(a+b-c)/4/(a+b+c)

r² = x*(y-c)/4/(y+c) < N²; x < N²*(y+c)*4/(y-c) ;
x = a*b; y = a+b

4*r²*(y+c) = x*(y-c)


--
(b+c-a))*(a+c-b) = x ; y² = (a+b)² = a²+b²+2*a*b; (a-b)² = a²+b²-2*a*b; y²-4*x = (a-b)²

(c-sq(y²-4*x))*(c+sq(y²-4*x)) = x
c²-y²+4*x = x
c²-y²+3*x = 0
y²-c² = 3*x
---

3,7,8 : 7*7 = 8*8+3*3-8*3 
a = 3, b = 8, c = 7, x = 24, y = 11
s = 9
r = sq(6*2*1/9) = sq(4/3) ~= 1.1547


----
y²-4*x > 0
y² > 4*x
3*x + c² = y²

c²  > x ; 
x = (y*y-c*c)/3

3*c²  > (y²-c²)
4*c²  > y²
2*c  > y
"""