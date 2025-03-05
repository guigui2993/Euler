import Euler
import math

"""
P195

60° angle => c is the side opposite
Diophantine Equation: a²-a*b+b²=c² => b = (a+-sqrt(4*c²-3*a²))/2

Hypothese: only postive => b = (a+sqrt(4*c²-3*a²))/2

=> search for: 4*c²-3*a² = n² <=> (C²-3*a²) = n² with C = 2*c

Pell's equation: a²-Ny²=k
solution: (m, 1, m²-N) => (a, y, k)
method2: ((a*m+N*b)/k, (a+b*m)/k, (m*m-N)/k)

C²-3*a² = k (=n²)
(m, 1, m²-3) => trivial solution, then
((C*m+3*b)/k, (C+b*m)/k, (m*m-3)/k)

list all trivial
for each trivial find : (m²-3)/k = n²
method 1 : combine trivial sols k1*k2
"""

#Trivial solutions

alls = {(2, 1, 1)}
mMax = 500
ts = []
#for m in range(0,mMax): # do we need m=0 ?
for m in range(-mMax,mMax): # do we need m<0 ?
    ts.append((m, 1, m*m-3))

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
kListNeg = {} #list of k < 0
cnt = 0
#for t in alls:
for t in ts:
    (a,b,k) = t

    if k<0:
        factors = Euler.factorization(-k)
        mul = 1
        for f in factors:
            if factors[f]%2 == 1:# ignore the squares, etc
                mul *= f

        if mul in kListNeg:
            kListNeg[mul].append(t)
        else:
            kListNeg[mul] = [t]

    else:
        factors = Euler.factorization(k)
        mul = 1
        for f in factors:
            if factors[f]%2 == 1:# ignore the squares, etc
                mul *= f

        if mul in kList:
            kList[mul].append(t)
        else:
            kList[mul] = [t]

    #if(k>=0 and k<=10):
    #print("{}:\t{}".format(t,mul))
    cnt+=1
    #print(Euler.factorization(k))
    
print(cnt)

#combination k1k2: k1 and k2 not square beside 1, so combine with 1 and the k having the same mul together
# combination k and 1

# we are interested in k = n²
# 1 trivial solution works: m=1 => k = 1
# other solutions must be a combination k1*k2

for mul in kList:
    for t in kList[mul]:
        (x1, y1, k1) = t
        # combination k1 and k2 having same mul
        for t2 in kList[mul]:
            (x2, y2, k2) = t2

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
            alls.add((x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2))
            alls.add((x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2))
            alls.add((x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2))


for mul in kListNeg:
    for t in kListNeg[mul]:
        (x1, y1, k1) = t
        # combination k1 and k2 <0 having same mul 
        for t2 in kListNeg[mul]:
            (x2, y2, k2) = t2

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
            alls.add((x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2))
            alls.add((x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2))
            alls.add((x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2))

#list incomplete repass with k2 = 1 k in alls
alls2 = set()
for (x1, y1, k1) in alls:
    for (x2, y2, k2) in alls:
        # do we need k<0 in alls ? TBC
        tn = (x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2)
        if tn[0] >0 and tn[0]%2==0 and tn[1] > 0:
            alls2.add(tn)

        tn = (x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2)
        if tn[0] >0 and tn[0]%2==0 and tn[1] > 0:
            alls2.add(tn)

        tn = (x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2)
        if tn[0] >0 and tn[0]%2==0 and tn[1] > 0:
            alls2.add(tn)
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

