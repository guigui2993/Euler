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
"""

#Trivial solutions

mMax = 10
# m == 0 & 1 => negative k -> their combination are below
#ts = [(3, -1, 6), (4, 2, 4), (3, 1, 6), (3, 0, 9), (4, -2, 4), (2, 0, 4)]
#ts = [(3, -1, 6), (4, 2, 4), (3, 0, 9), (4, -2, 4), (2, 0, 4)]
ts = [(3, -1, 6)]
for m in range(3,mMax): # do we need m<0 ?
    ts.append((m, 1, m*m-3))

print("ts size: {}".format(len(ts)))
"""
for t in ts:
    (a,b,k) = t
    if(k>=-10 and k <=10):
        print(t)
exit()
"""
#for all trivial solution find the multiplier needed to make it square
#ex: k1 = 12 => we need k2 multiple of 3 so that k1*k2 = n²
#kLsit = {mul: [k, ]} i.e. {6: [6, 24, ...]}
kList = {}
cnt = 0
#for t in alls:
for t in ts:
    (a,b,k) = t

    factors = Euler.factorization(k)
    mul = 1
    kSq = 1
    for f in factors:
        if factors[f]%2 == 1:# ignore the squares, etc
            mul *= f
        kSq *= f**(factors[f]//2)

    kSq *= mul
    if mul in kList:
        kList[mul].append((a, b, kSq))
    else:
        kList[mul] = [(a, b, kSq)]

    cnt+=1

    #if(k>=0 and k<=10):
    #print("{}:\t{}".format(t,mul))
    #print(Euler.factorization(k))

print("kList size: {}".format(cnt))

print("#"*20)
#print(kList)

#combination k1k2: k1 and k2 not square beside 1, so combine with 1 and the k having the same mul together
# combination k and 1

# we are interested in k = n²
# 1 trivial solution works: m=1 => k = 1
# other solutions must be a combination k1*k2
alls = {(4, 2, 4), (3, 0, 9), (4, -2, 4), (2, 0, 4), (2, 1, 1)}
kSqList = {1: {(2, 1, 1)}, 2: {(2, 0, 1), (4, -2, 1), (4, 2, 1)}, 3: {(3, 0, 1)}} #mul: (x, y, sqrt(k)/mul)
for mul in kList:
    for t in kList[mul]:
        (x1, y1, kSq1) = t
        # combination k1 and k2 having same mul
        for t2 in kList[mul]:
            (x2, y2, kSq2) = t2

            #if mul
            """
            tn = (x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2)
            if tn[0] >0 and tn[1] > 0:
                alls.add(tn)
            tn = (x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2)
            if tn[0] >0 and tn[1] > 0:
                alls.add(tn)
            tn = (x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2)
            if tn[0] >0 and tn[1] > 0:
                alls.add(tn)
            """
            #alls.add((x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2))
            #alls.add((x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2))
            #alls.add((x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2))

            (x, y, kSq) = (x1*x2+3*y1*y2, x1*y2+x2*y1, kSq1*kSq2)
            if mul in kSqList:
                kSqList[mul].add((x, y, kSq))
            else:
                kSqList[mul] = {(x, y, kSq)}
            (x, y, kSq) = (x1*x2-3*y1*y2, x1*y2-x2*y1, kSq1*kSq2)
            if mul in kSqList:
                kSqList[mul].add((x, y, kSq))
            else:
                kSqList[mul] = {(x, y, kSq)}
            (x, y, kSq) = (x1*x2-3*y1*y2, x2*y1-x1*y2, kSq1*kSq2)
            if mul in kSqList:
                kSqList[mul].add((x, y, kSq))
            else:
                kSqList[mul] = {(x, y, kSq)}

            #k = mul*mul*kSq1*kSq1*kSq2*kSq2
            #kSq = kSq1*kSq2




# combine the kSquare between themself
print("Yo")
print(len(alls))

rr2 = 10000
for mul in kSqList:
    for t in kSqList[mul]:
        (x, y, kSq) = t
        if x <=0 or y <= 0:
            continue
        print("{}\t{}\t{}".format(x, y, kSq))
        C = x
        a = y
        k = mul*kSq
        nSq = k

        if C%2 != 0:
            #print("C not multiple of 2")
            continue
        c = C//2
        if (a+nSq)%2 != 0:
            #print("a+nSq not multiple of 2")
            continue
        b = (a+nSq)//2
        s = (a+b+c)/2
        if (s-a)*(s-b)*(s-c)/s > rr2:
            continue
        if nSq == a:
            continue
        print("\t\t\t{}\t{}\t{}".format(a, b, c))

exit()

alls2 = {(4, 2, 4), (3, 0, 9), (4, -2, 4), (2, 0, 4), (2, 1, 1)}
for (x1, y1, k1) in alls:
    for (x2, y2, k2) in alls:
        tn = (x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2)
        if tn[0] >0 and tn[0]%2==0 and tn[1] > 0:
            alls2.add(tn)

        tn = (x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2)
        if tn[0] >0 and tn[0]%2==0 and tn[1] > 0:
            alls2.add(tn)

        tn = (x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2)
        if tn[0] >0 and tn[0]%2==0 and tn[1] > 0:
            alls2.add(tn)

print(len(alls2))

rr2 = 10000
cnt = 0
for t in alls2:
    (C,a,n) = t
    c = C//2
    nSq = int(math.sqrt(n))
    b = (a+nSq)/2
    s = (a+b+c)/2
    if (s-a)*(s-b)*(s-c)/s > rr2:
        continue
    if nSq == a:
        continue

    print("{}\t{}\t{} => {}".format(a,b,c, a*a+b*b-a*b))
    cnt += 1

print(cnt)
"""
if(n>=1 and n <=10):
    #print(t)
    print("{}\t{}\t{} => {}".format(a,b,c, a*a+b*b-a*b))
"""