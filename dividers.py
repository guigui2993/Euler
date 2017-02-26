

# small scrypt that enumerate every dividers of a number

import Euler

n = 720

facs = Euler.factorization(n)

print(facs)

e,f = [],[]
for k in facs:
	e.append(facs[k])
	f.append(int(k))


it = [0]*len(f)

cont = True
d = 1
while cont:
	#print(it)
	print(d)

	a = 0
	it[a] += 1
	d *= f[a]
	while it[a] > e[a]:
		it[a] = 0
		d //= f[a]**(e[a]+1)
		a += 1
		d *= f[a]
		if a >= len(e):
			cont = False
			break
		it[a] += 1
		d *= f[a]

#print(it)
