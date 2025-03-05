"""
Pell's equation:
a²-Ny²=k
solution: (m, 1, m²-N) => (a, y, k)
((a*m+N*b)/k, (a+b*m)/k, (m*m-N)/k)

Try 2 methods to list all solutions to a²-3b²=k

C²-3*a² = k (=n²)
(m, 1, m²-3) => trivial solution, then
((C*m+3*b)/k, (C+b*m)/k, (m*m-3)/k)

list all trivial
for each trivial find : (m²-3)/k = n²

(1, 1, -2), (2, 1, 1), (3, 1, 6), (4, 1, 13)

ex:
(m²-3)/6 => m = 9
    k = 13, b = 2, a = 5 (5, 2, 13) 25-3*4 = 13

# (x1*x2+N*y1*y2, x1*y2+x2*y1, k1k2) (x1*x2-N*y1*y2, x1*y2-x2*y1, k1k2) other solutions
# (x1*x2+3*y1*y2, x1*y2+x2*y1, k1k2) (x1*x2-3*y1*y2, x1*y2-x2*y1, k1k2) other solutions
(2, 1, 1) (4, 1, 13)
(8+3, 2+4, 13) < 11²-3*6² = 
(8-3, 2-4, 13)

"""

#Trivial solutions

alls = set()
mMax = 100
ts = []
#for m in range(0,mMax): # do we need m=0 ?
for m in range(-mMax,mMax): # do we need m<0 ?
    ts.append((m, 1, m*m-3))
    alls.add((m, 1, m*m-3))

#method 1
for t1 in ts:
    (x1, y1, k1) = t1
    for t2 in ts:
        (x2, y2, k2) = t2

        alls.add((x1*x2+3*y1*y2, x1*y2+x2*y1, k1*k2))
        alls.add((x1*x2-3*y1*y2, x1*y2-x2*y1, k1*k2))
        alls.add((x1*x2-3*y1*y2, x2*y1-x1*y2, k1*k2))
cnt = 0
for t in alls:
    (a,b,k) = t
    if(k>=0 and k<=10):
        print(t)
        cnt+=1
print(cnt)

#method 2
all2 = set()
for t1 in ts:
    (a,b,k) = t1
    for m in range(-mMax,mMax):
        if (a+b*m)%k==0 and (a*m+3*b)%k==0 and (m*m-3)%k==0:
            all2.add(((a*m+3*b)//k, (a+b*m)//k, (m*m-3)//k))


cnt = 0
for t in all2:
    (a,b,k) = t
    if(k>=0 and k<=10):
        print(t)
        cnt+=1
print(cnt)
