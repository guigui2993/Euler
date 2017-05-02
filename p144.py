# -*- coding: utf-8 -*-
"""
Created on Thu Apr 13 09:04:38 2017

@author: lempereu
p144 Ellipse
"""
import math

a_x, a_y = 0.0,10.1

o_x, o_y = 1.4,-9.6


x_a, y_a = o_x-a_x, o_y-a_y

m = -4*o_x/o_y

d_x, dy = 1, m

r_y = math.sqrt(x_a**2+y_a**2)/(x_a+y_a*m)/math.sqrt(1+m**2)
r_x = -m*r_y

# slope reflexion
r_m = (o_y-r_y)/(o_x-r_y)

y_r_0 = r_y-r_x*r_m

b_m, b_M = 0, 0

if r_m < 0 and o_y > 0:
    if y_r_0 > 10:
        b_m, b_M = 0, 5
    else:
        b_m, b_M = -5, 0
elif r_m < 0 and o_y < 0:
    if y_r_0 < -10:
        b_m, b_M = 0, 5
    else:
        b_m, b_M = -5, 0
elif r_m > 0 and o_y < 0:
    if y_r_0 < -10:
        b_m, b_M = 0, 5
    else:
        b_m, b_M = -5, 0
elif r_m > 0 and o_y > 0:
    if y_r_0 < 10:
        b_m, b_M = -5, 0
    else:
        b_m, b_M = 0, 5
else:
    print("What the Fock !")
    exit(-5)


tol = 10**-8

while (b_m + b_M)/2 > tol:
    
    
"""
#v_i = (i_x-o_x,i_y-o_y)
#slope = -4*i_x/i_y
if i_x != 0:
    tan = i_y/(4*i_x)
else:
    print("The beam goes out")
    exit(-2)

# y = m*x + p
# m = tan
# p = y-m*x
p = i_y-tan*i_x

delta = -16*p*p+400*m*m+1600
if delta < 0.0:
    print("No impact => problem")
    exit(-1)

ni_x = (-2*m*p + math.sqrt(delta))/2/(m*m+4)

if ni_x < -5.0 or ni_x > 5.0:
    print("Troubles !")
    exit(-3)
"""
