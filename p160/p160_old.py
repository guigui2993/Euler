# -*- coding: utf-8 -*-
"""
Created on Mon Oct 10 09:40:07 2022

@author: lempereu
"""

"""
m = 1
for i in range(101,200):
    print(i)
    m *= i
print(m)





for d in range(10):
    m = 1
    for i in range(d*100+1,d*100+101):
        if (i%10 == 2 or i%5==0):
            #print(i)
            m *= i
            continue
    
    while m%10==0:
        m//=10
    a = m%100
    print(a)
    
    m = 1
    for i in range(d*100+1001,d*100+1101):
        if (i%10 == 2 or i%5==0):
            #print(i)
            m *= i
            continue
    
    while m%10==0:
        m//=10
    b = m%100
    print(b)
    
    print()

m=1
"""

"""
    for i in range(d*100+1,(d+1)*100+1):
        if not(i%10 == 2 or i%5==0):
            #print(i)
            m *= i
            continue
        
    #print(m)
    b = m%100

    print(str(int(a))+ "\t" + str(b))

"""


def fac(n):
    r = 1
    for i in range(1,n+1):
        r *= i
    return r

f = fac(999)

while f%10==0:
    f//=10

f = f**10
for i in range(1,11):
    f *= i*1000

while f%10==0:
    f//=10


print(f%100)


f = fac(10000)

while f%10==0:
    f//=10
    
print(f%100)

m = 1
for i in range(1,100):
    if i%10!=0:
        m *= i

print("/10: "+ str(m))

"""
print(fac(3))

print(fac(100))
print(323680510640043784471297807946262418177301256542924258862716038557541153440651473035605563988567102078345805824*288328188989202616590336000000000000000000000000)
"""

"""
# n > return fac of n-1 % 100
def fm(n):
    m = 1
    for i in range(10):
        return m *= fm(n//10*i)
    
    return m

"""

print()

f = fac(99)

while f%10==0:
    f//=10

f = f%100
f = f**9

f *= fac(999)*fac(9)

while f%10==0:
    f//=10
    
print(f)

f = fac(10000)

while f%10==0:
    f//=10
    
print(f%100)



#----------
print("-"*20)

f = 1
for i in range(1,11):
    f *= i*1000

while f%10==0:
    f//=10
    
print(f%100)

f = fac(10000)
while f%10==0:
    f//=10
    
print("ans = {}".format(f%100))

#@print(64**100)

f = 64* (28**100) * 64 * 64
while f%10==0:
    f//=10
print(f%100)


#--------------


s = {}
c = 0
for i in range(1,101):
    s[i*100] = 1
    c += 1

for i in range(0,100):
    for j in range(1,100):
        #if j%10 != 0:
        s[i*100+j] = 1
        c += 1

#-------------

s = {}
c = 0
for i in range(1,101):
    s[i*100] = 1
    c += 1

for i in range(0,100):
    for j in range(1,100):
        if i%100>=10 and j%10 != 0:
            s[i*100+j] = 1
            c += 1
        elif i%100<10 or j%10 == 0:
            s[i*100+j] = 1
            c += 1

"""    
#-------------

s = {}
c = 0
for i in range(1,101):
    s[i*100] = 1
    c += 1

for i in range(0,10):
    for j in range(1,100):
        if j%10 != 0:
            s[i*100+j] = 1
            c += 1

for i in range(11,100):
    for j in range(1,100):
        if j%10 != 0:
            s[i*100+j] = 1
            c += 1
"""
"""
for i in range(1,100):
    s[i*10] = 1
    c += 1
"""

#-------------

s = {}
c = 0
f= 1
#1-100 00 => 100
for i in range(1,101):
    s[i*100] = 1
    c += 1
    f *= i*100
    

#00xx => 99
for i in range(1,100):
    s[i] = 1
    c += 1
    f *= i

#01xx - 09xx %10==0 => 9*9
for i in range(1,10):
    for j in range(1,10):
        s[i*100+j*10] = 1
        c += 1
        f *= i*100+j*10

#01xx - 09xx - 1-99\ 10 => 9*90
for i in range(1,10):
    for j in range(1,100):
        if j%10 != 0:
            s[i*100+j] = 1
            c += 1
            f *= i*100+j

#10xx - 99xx \ %10 - 1-99 =>90*99
for i in range(11,100):
    for j in range(1,100):
        if i%10!=0:
            s[i*100+j] = 1
            c += 1
            f *= i*100+j

#10xx - 99xx %10==0 - 1-99
for i in range(1,10):
    for j in range(1,100):
        s[i*1000+j] = 1
        c += 1
        f *= i*1000+j

while f%10==0:
    f//=10
print("rest:{} <> {}".format(f%100, 64*64*56*64)) # **90  *28**9


#print(s)
print(len(s))
print(c)


"""
f = 64*64*28**9 * 64**90
while f%10==0:
    f//=10
print(f%100)

f = 1
for i in range(11,100):
    if i%10!=0:
        f*=i
while f%10==0:
    f//=10
print(f%100)


#test
print("test:")

f = 1
#10xx - 99xx - 1-99
for i in range(1001,1100):
    f *= i
    print(i)

while f%10==0:
    f//=10
    
print("rest:{} ".format(f%100)) # **90  *28**9
f = 1
#10xx - 99xx - 1-99
for i in range(1,100):
    f *= i

while f%10==0:
    f//=10
    
print("rest:{} ".format(f%100)) # **90  *28**9

print(1001*1002*1003*1004*1005*1006*1007*1008*1009*1010*1011*1012*1013*1014*1015*1016*1017*1018*1019*1020*1021*1022*1023*1024*1025*1026*1027*1028*1029*1030*1031*1032*1033*1034*1035*1036*1037*1038*1039*1040*1041*1042*1043*1044*1045*1046*1047*1048*1049*1050*1051*1052*1053*1054*1055*1056*1057*1058*1059*1060*1061*1062*1063*1064*1065*1066*1067*1068*1069*1070*1071*1072*1073*1074*1075*1076*1077*1078*1079*1080*1081*1082*1083*1084*1085*1086*1087*1088*1089*1090*1091*1092*1093*1094*1095*1096*1097*1098*1099)

"""