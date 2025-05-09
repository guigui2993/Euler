import random

def primesbelow(N):
	# http://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n-in-python/3035188#3035188
	#""" Input N>=6, Returns a list of primes, 2 <= p < N """
	correction = N % 6 > 1
	N = {0:N, 1:N-1, 2:N+4, 3:N+3, 4:N+2, 5:N+1}[N%6]
	sieve = [True] * (N // 3)
	sieve[0] = False
	for i in range(int(N ** .5) // 3 + 1):
		if sieve[i]:
			k = (3 * i + 1) | 1
			sieve[k*k // 3::2*k] = [False] * ((N//6 - (k*k)//6 - 1)//k + 1)
			sieve[(k*k + 4*k - 2*k*(i%2)) // 3::2*k] = [False] * ((N // 6 - (k*k + 4*k - 2*k*(i%2))//6 - 1) // k + 1)
	return [2, 3] + [(3 * i + 1) | 1 for i in range(1, N//3 - correction) if sieve[i]]

smallprimeset = set(primesbelow(100000))
_smallprimeset = 100000
def isprime(n, precision=7):
	# http://en.wikipedia.org/wiki/Miller-Rabin_primality_test#Algorithm_and_running_time
	if n < 1:
		raise ValueError("Out of bounds, first argument must be > 0")
	elif n <= 3:
		return n >= 2
	elif n % 2 == 0:
		return False
	elif n < _smallprimeset:
		return n in smallprimeset


	d = n - 1
	s = 0
	while d % 2 == 0:
		d //= 2
		s += 1

	for repeat in range(precision):
		a = random.randrange(2, n - 2)
		x = pow(a, d, n)

		if x == 1 or x == n - 1: continue

		for r in range(s - 1):
			x = pow(x, 2, n)
			if x == 1: return False
			if x == n - 1: break
		else: return False

	return True

# https://comeoncodeon.wordpress.com/2010/09/18/pollard-rho-brent-integer-factorization/
def pollard_brent(n):
	if n % 2 == 0: return 2
	if n % 3 == 0: return 3

	y, c, m = random.randint(1, n-1), random.randint(1, n-1), random.randint(1, n-1)
	g, r, q = 1, 1, 1
	while g == 1:
		x = y
		for i in range(r):
			y = (pow(y, 2, n) + c) % n

		k = 0
		while k < r and g==1:
			ys = y
			for i in range(min(m, r-k)):
				y = (pow(y, 2, n) + c) % n
				q = q * abs(x-y) % n
			g = gcd(q, n)
			k += m
		r *= 2
	if g == n:
		while True:
			ys = (pow(ys, 2, n) + c) % n
			g = gcd(abs(x - ys), n)
			if g > 1:
				break

	return g

smallprimes = primesbelow(1000) # might seem low, but 1000*1000 = 1000000, so this will fully factor every composite < 1000000
def primefactors(n, sort=False):
	factors = []

	for checker in smallprimes:
		while n % checker == 0:
			factors.append(checker)
			n //= checker
		if checker > n: break

	if n < 2: return factors

	while n > 1:
		if isprime(n):
			factors.append(n)
			break
		factor = pollard_brent(n) # trial division did not fully factor, switch to pollard-brent
		factors.extend(primefactors(factor)) # recurse to factor the not necessarily prime factor returned by pollard-brent
		n //= factor

	if sort: factors.sort()

	return factors

def factorization(n):
	factors = {}
	for p1 in primefactors(n):
		try:
			factors[p1] += 1
		except KeyError:
			factors[p1] = 1
	return factors

totients = {}
def totient(n):
	if n == 0: return 1

	try: return totients[n]
	except KeyError: pass

	tot = 1
	for p, exp in factorization(n).items():
		tot *= (p - 1)  *  p ** (exp - 1)

	totients[n] = tot
	return tot

def gcd(a, b):
	if a == b: return a
	while b > 0: a, b = b, a % b
	return a

def lcm(a, b):
	return abs((a // gcd(a, b)) * b)

def extendedGcd(a,b):
	x,y = 0,1
	lastx,lasty = 1,0

	while b:
		q = a//b
		
		a,b = b,a%b
		lastx,x = x,lastx-q*x
		lasty,y = y,lasty-q*y
	
	return (lastx,lasty,a)

def equationMod(a,b,n):
	r = extendedGcd(a,n)
	if r == 0:
		return 0
	x,y,d = r

	if b%d:
		return 0

	ans = []
	x_0 = (x*b//d) % n
	for i in range(d):
		ans.append((x_0+i*(n//d))%n)
	
	return ans

# factorial of n
def fact(n):
    assert n>=0 and int(n) == n, "factorial f(n); n must be positive integer or 0!"
    def fact_(n):
        if n < 3:
            if n==0:
                return 1
            return n
        return n*fact_(n-1)
    return fact_(n)

# number of combination without repetition
# n: set size
# k: the number of item taken from the set
def nbCombNoR(n, k):
    return fact(n)//fact(n-k)//fact(k)

# combination without repetition
# v:    the set of item
# t:    the remaining number of item to take
# out:  the output list of all combination
def combNoR(v, t, out):
    assert t > 0 and t <= len(v), "0 < t < len(v) !"
    lst = []
    #s start item
    #t nb of item to take
    def combNoR_(s, t):
        for i in range(s, len(v)):
            if t == 1: # last to take
                lst.append(v[i])
                out.append(lst[:])
                lst.pop()
            else:
                lst.append(v[i])
                combNoR_(i+1, t-1)
                lst.pop()
    combNoR_(0, t)

if __name__ == '__main__':
	a = 1009
	b = 5151
	print(extendedGcd(a,b))
	#print(equationMod(6,9,15))
	n = 42
	print(factorization(n))
