

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
while cont:
	print(it)

	a = 0
	it[a] += 1
	while it[a] > e[a]:
		it[a] = 0
		a += 1
		if a >= len(e):
			cont = False
			break
		it[a] += 1

#print(it)
