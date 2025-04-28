# answer not 1185699923676123326860
# ans not 15083658808892098833182496745244412345
sq_lst = {} #list of square f(n) with the nb of way to make it
comp = {0: 20, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0}
sqrt = {}
mask = 11111111111111111111
for i in range(1, 41):
    sqrt[i*i] = True

fac = {1: 1}
for i in range(2, 21):
    fac[i] = fac[i-1]*i

summ = 0
def isSqrt(n):
    global summ
    if(n in sqrt):
        #permutation without repetition
        #p = fac[20]
        p = fac[20-comp[0]]
        #for i in range(10):
        for i in range(1,10):
            if comp[i] > 1:
                p //= fac[comp[i]]

        p //= 20
        for c in comp:
            if comp[c] > 0:
                summ += p * comp[c] * mask * c
        """
        if n in sq_lst:
            sq_lst[n] += p
        else:
            sq_lst[n] = p
        """
        return True
    return False

kk = 0
cc = 0
"""
print(kk)
print(cc)
print(len(sq_lst))
"""
for a in range(1, 10):
    cc += 1
    n_a = a*a
    comp[0] -= 1
    comp[a] += 1
    if(isSqrt(n_a)):
        kk += 1 #always sqrt


    for b in range(a, 10):
        comp[0] -= 1
        comp[b] += 1
        n_b = n_a+b*b
        if(isSqrt(n_b)):
            kk +=1
        cc +=1
        for c in range(b, 10):
            comp[0] -= 1
            comp[c] += 1
            n_c = n_b+c*c
            if(isSqrt(n_c)):
                kk +=1
            cc +=1
            for d in range(c, 10):
                comp[0] -= 1
                comp[d] += 1
                n_d = n_c+d*d
                if(isSqrt(n_d)):
                    kk +=1
                cc +=1
                for e in range(d, 10):
                    comp[0] -= 1
                    comp[e] += 1
                    n_e = n_d+e*e
                    if(isSqrt(n_e)):
                        kk +=1
                    cc +=1
                    for f in range(e, 10):
                        comp[0] -= 1
                        comp[f] += 1
                        n_f = n_e+f*f
                        if(isSqrt(n_f)):
                            kk +=1
                        cc +=1
                        for g in range(f, 10):
                            comp[0] -= 1
                            comp[g] += 1
                            n_g = n_f+g*g
                            if(isSqrt(n_g)):
                                kk +=1
                            cc +=1
                            for h in range(g, 10):
                                comp[0] -= 1
                                comp[h] += 1
                                n_h = n_g+h*h
                                if(isSqrt(n_h)):
                                    kk +=1
                                cc +=1
                                for i in range(h, 10):
                                    comp[0] -= 1
                                    comp[i] += 1
                                    n_i = n_h+i*i
                                    if(isSqrt(n_i)):
                                        kk +=1
                                    cc +=1
                                    for j in range(i, 10):
                                        comp[0] -= 1
                                        comp[j] += 1
                                        n_j = n_i+j*j
                                        if(isSqrt(n_j)):
                                            kk +=1
                                        cc +=1
                                        for k in range(j, 10):
                                            comp[0] -= 1
                                            comp[k] += 1
                                            n_k = n_j+k*k
                                            if(isSqrt(n_k)):
                                                kk +=1
                                            cc +=1
                                            for l in range(k, 10):
                                                comp[0] -= 1
                                                comp[l] += 1
                                                n_l = n_k+l*l
                                                if(isSqrt(n_l)):
                                                    kk +=1
                                                cc +=1
                                                for m in range(l, 10):
                                                    comp[0] -= 1
                                                    comp[m] += 1
                                                    n_m = n_l+m*m
                                                    if(isSqrt(n_m)):
                                                        kk +=1
                                                    cc +=1
                                                    for n in range(m, 10):
                                                        comp[0] -= 1
                                                        comp[n] += 1
                                                        n_n = n_m+n*n
                                                        if(isSqrt(n_n)):
                                                            kk +=1
                                                        cc +=1
                                                        for o in range(n, 10):
                                                            comp[0] -= 1
                                                            comp[o] += 1
                                                            n_o = n_n+o*o
                                                            if(isSqrt(n_o)):
                                                                kk +=1
                                                            cc +=1
                                                            for p in range(o, 10):
                                                                comp[0] -= 1
                                                                comp[p] += 1
                                                                n_p = n_o+p*p
                                                                if(isSqrt(n_p)):
                                                                    kk +=1
                                                                cc +=1
                                                                for q in range(p, 10):
                                                                    comp[0] -= 1
                                                                    comp[q] += 1
                                                                    n_q = n_p+q*q
                                                                    if(isSqrt(n_q)):
                                                                        kk +=1
                                                                    cc +=1
                                                                    for r in range(q, 10):
                                                                        comp[0] -= 1
                                                                        comp[r] += 1
                                                                        n_r = n_q+r*r
                                                                        if(isSqrt(n_r)):
                                                                            kk +=1
                                                                        cc +=1
                                                                        for s in range(r, 10):
                                                                            comp[0] -= 1
                                                                            comp[s] += 1
                                                                            n_s = n_r+s*s
                                                                            if(isSqrt(n_s)):
                                                                                kk +=1
                                                                            cc +=1
                                                                            for t in range(s, 10):
                                                                                comp[0] -= 1
                                                                                comp[t] += 1
                                                                                n_t = n_s+t*t
                                                                                if(isSqrt(n_t)):
                                                                                    kk +=1
                                                                                cc +=1
                                                                                comp[t] -= 1
                                                                                comp[0] += 1
                                                                            comp[s] -= 1
                                                                            comp[0] += 1
                                                                        comp[r] -= 1
                                                                        comp[0] += 1
                                                                    comp[q] -= 1
                                                                    comp[0] += 1
                                                                comp[p] -= 1
                                                                comp[0] += 1
                                                            comp[o] -= 1
                                                            comp[0] += 1
                                                        comp[n] -= 1
                                                        comp[0] += 1
                                                    comp[m] -= 1
                                                    comp[0] += 1
                                                comp[l] -= 1
                                                comp[0] += 1
                                            comp[k] -= 1
                                            comp[0] += 1
                                        comp[j] -= 1
                                        comp[0] += 1
                                    comp[i] -= 1
                                    comp[0] += 1
                                comp[h] -= 1
                                comp[0] += 1
                            comp[g] -= 1
                            comp[0] += 1
                        comp[f] -= 1
                        comp[0] += 1
                    comp[e] -= 1
                    comp[0] += 1
                comp[d] -= 1
                comp[0] += 1
            comp[c] -= 1
            comp[0] += 1
        comp[b] -= 1
        comp[0] += 1
    comp[a] -= 1
    comp[0] += 1

print(kk)
print(cc)
print(len(sq_lst))
print(sq_lst)
"""
su = 0
for sq in sq_lst:
    #print("{}\t{}".format(sq, sq_lst[sq]))
    #su += sq*sq_lst[sq]
    su += sq_lst[sq]
"""
print(summ)
