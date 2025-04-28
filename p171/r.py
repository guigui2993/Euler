"""
p171

# answer not 1185699923676123326860
# ans not 15083658808892098833182496745244412345
# not 14489966520041833112955100334799581668869
# not 104861799630145491143395826448142989533
works for 3 not 4

try recursive
"""
import sys

sq_lst = {} #list of square f(n) with the nb of way to make it
NBD = int(sys.argv[1]) # nb of digits
comp = {0: NBD, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0}
sqrt = {}
mask = 0
for i in range(NBD):
    mask += 10**i

for i in range(1, 41):
    sqrt[i*i] = True

fac = {1: 1}
for i in range(2, 21):
    fac[i] = fac[i-1]*i
dbg ={}
summ = 0
def isSqrt(n):
    global summ
    if(n in sqrt):
        m = ""
        for c in comp:
            m += str(c)*comp[c]
        #print(m)
        #permutation without repetition
        p = fac[NBD]
        for i in range(10):
            if comp[i] > 1:
                p //= fac[comp[i]]

        p //= NBD
        tt = 0
        if p == 0:
            for c in comp:
                tt = mask * c
        else:
            for c in comp:
                if comp[c] > 0:
                    tt += p * comp[c] * mask * c
        summ += tt
        dbg[m] = tt
        return True
    return False

kk = 0
cc = 0
"""
print(kk)
print(cc)
print(len(sq_lst))
"""
# n: sum of all sq digits
# digMin : digit starts
# d: depth
def r(n, digMin, d):
    #print("{}\t{}\t{}".format(n, digMin, d))
    global kk
    if d > NBD: # reach the nb of digits
        return

    for i in range(digMin, 10):
        n += i*i
        comp[0] -= 1
        comp[i] += 1
        if(isSqrt(n)):
            kk += 1
        r(n, i, d+1)
        n -= i*i
        comp[0] += 1
        comp[i] -= 1
r(0, 1, 1)
print(dbg)
print(kk)
print(summ)
