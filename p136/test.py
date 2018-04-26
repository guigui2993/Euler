
lim = 3000

l = [[] for i in range(250)]

for r in range(1,lim):
    for d in range(1,r):
        if r*r-d*d < 250:
            l[r*r-d*d].append((r,d))

for k in range(len(l)):
    #print(k, l[k])
    if k%4 == 2 and len(l[k]) > 0:
        print(k)
