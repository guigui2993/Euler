import Euler
import math

"""
P195

60° angle => c is the side opposite
Diophantine Equation: a²-a*b+b²=c²
=> b = (a+-sqrt(4*c²-3*a²))/2

Hypothese: only postive
=> b = (a+sqrt(4*c²-3*a²))/2

=> search for:
4*c²-3*a² = n² <=> (C²-3*a²) = n² with C = 2*c


Pell's equation:
a²-Ny²=k
solution: (m, 1, m²-N) => (a, y, k)
((a*m+N*b)/k, (a+b*m)/k, (m*m-N)/k)

C²-3*a² = k (=n²)
(m, 1, m²-3) => trivial solution, then
((C*m+3*b)/k, (C+b*m)/k, (m*m-3)/k)

Method 2:
list all trivial
Combine trivial solution so k1*k2 = n²
            ((x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2))
            ((x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2))
            ((x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2))

for each trivial solution, we find (m, 1, m²-3) with m >0 and <0
We can drop the m<0 because their solution will end up with a <0

should focus on prime solution not n*(a, b, c)
try something

#should find 1234 !
nMax = 946 => 1027 below 100 (945 => 843)

4 missing:
a	b	c
187	280	247
247	352	313
279	319	301
280	391	349

C	a	nSq
494	187	373
626	247	457
602	279	359
698	280	502

try to improve
"""

#Trivial solutions
import sys

mMax = 1000
mMax = int(sys.argv[1])
ts = []
for m in range(3,mMax): # do we need m<0 ?
    ts.append((m, 1, m*m-3))

print("ts size: {}".format(len(ts)))
#print(ts)
#print("§"*20)

#for all trivial solution find the multiplier needed to make it square
#ex: k1 = 12 => we need k2 multiple of 3 so that k1*k2 = n²
#kLsit = {mul: [k, ]} i.e. {6: [6, 24, ...]}
kList = {}
cnt = 0
for t in ts:
    (a,b,k) = t

    factors = Euler.factorization(k)
    mul = 1
    kSq = 1
    for f in factors:
        if factors[f]%2 == 1:# ignore the squares, etc
            mul *= f
        kSq *= f**(factors[f]//2)

    if mul in kList:
        kList[mul].append((a, b, kSq))
    else:
        kList[mul] = [(a, b, kSq)]

    cnt+=1

print("kList size: {}".format(cnt))

""" #DBG
print("#"*20)
print(kList)
print("#"*20)
"""
#combination k1k2: k1 and k2 not square beside 1, so combine with 1 and the k having the same mul together
# combination k and 1

# we are interested in k = n²
# 1 trivial solution works: m=1 => k = 1
# other solutions must be a combination k1*k2
xyk = {(2, 1, 1), (2, -1, 1), (1, 0, 1)} # (x, y, sqK)


# TODO gcd(x, y, kSq) = 1
# TODO check if (1, 0, 1) required

def ad(s, mul, x, y, kSq):
    gcd = Euler.gcd(Euler.gcd(x,y), kSq*mul)

    s.add((x//gcd, y//gcd, (kSq*mul)//gcd))

for mul in kList:
    for t in kList[mul]:
        (x1, y1, kSq1) = t
        # combination k1 and k2 having same mul
        for t2 in kList[mul]:
            (x2, y2, kSq2) = t2

            (x, y, kSq) = (x1*x2+3*y1*y2, x1*y2+x2*y1, kSq1*kSq2)
            if x > 0 and y > 0 and kSq != y:
                ad(xyk, mul, x, y, kSq)

            (x, y, kSq) = (x1*x2-3*y1*y2, x1*y2-x2*y1, kSq1*kSq2)
            if x > 0 and y > 0 and kSq != y:
                ad(xyk, mul, x, y, kSq)

            (x, y, kSq) = (x1*x2-3*y1*y2, x2*y1-x1*y2, kSq1*kSq2)
            if x > 0 and y > 0 and kSq != y:
                ad(xyk, mul, x, y, kSq)

print("xyk size: {}".format(len(xyk)))
r2LIM = 10000
"""
#DBG
for t in xyk:
    (x, y, kSq) = t
    #if Euler.gcd(Euler.gcd(x,y), kSq) != 1:
    print("{}\t{}\t{}".format(x, y, kSq))
print("nb of xyk: {}".format(len(xyk)))
exit()
"""
xyk2 = set()
for (x, y, k) in xyk:
    xyk2.add((x, y, k))

### TRY COMBINATION ####
for (x1, y1, k1) in xyk:
    for (x2, y2, k2) in xyk:
        (x, y, kSq) = (x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2)
        if x > 0 and y > 0 and kSq != y:
            ad(xyk2, 1, x, y, kSq)

        (x, y, kSq) = (x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2)
        if x > 0 and y > 0 and kSq != y:
            ad(xyk2, 1, x, y, kSq)

        (x, y, kSq) = (x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2)
        if x > 0 and y > 0 and kSq != y:
            ad(xyk2, 1, x, y, kSq)
### END COMBINATION ####
"""#DBG
for t in xyk2:
    (x, y, kSq) = t
    #if Euler.gcd(Euler.gcd(x,y), kSq) != 1:
    print("{}\t{}\t{}".format(x, y, kSq))
print("nb of xyk: {}".format(len(xyk)))
exit()
"""
print("xyk2 size: {}".format(len(xyk2)))
#triLst = {(5, 8, 7)}
triLst = set()

cc = 0
for t in xyk2:
    (C, a, nSq) = t # (x, y, kSq) = t

    #DBG
    if nSq == 373:
        print("found\t{}".format((C, a, nSq)))
        #exit()
    #DBG

    if C <=0 or a <= 0 or nSq == a:
        continue

    if C%2 != 0: #take the double if C%2 != 0
        (C, a, nSq) = (2*C, 2*a, 2*nSq)

    c = C//2
    if (a+nSq)%2 != 0:#never happen !!! #print("a+nSq not multiple of 2")
        continue
    b = (a+nSq)//2
    s = (a+b+c)/2

    r2 = (s-a)*(s-b)*(s-c)/s
    if r2 > r2LIM:
        continue
    nbTri = int(math.sqrt(r2LIM/r2))

    if b < a:
        a, b = b, a
    if c < b:
        c, b = b, c
    if c < a:
        c, a = a, c

    """
    if (a, b, c) in triLst:
        print("DUP !!!")
        exit()
    if Euler.gcd(a,Euler.gcd(b,c)) != 1:
        print("GCD !!!")
        exit()
    """
    if (a, b, c) in triLst or (b, c, a) in triLst or (c, a, b) in triLst or (a, c, b) in triLst or (b, a, c) in triLst or (c, b, a) in triLst: # useless
        continue
        print("dupy")
        print((a, b, c))
        #exit()


    cc += nbTri
    triLst.add((a, b, c))
    #print("\t\t\t{}\t{}\t{}".format(a, b, c))
    #print("{}\t{}\t{}\t\t{}".format(a, b, c, nbTri))

print("Nb of tri: {}".format(len(triLst)))
print("ans: {}".format(cc))
