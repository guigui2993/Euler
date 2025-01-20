# -*- coding: utf-8 -*-
"""
Created on Wed Dec 28 19:12:20 2022

@author: guill
"""

# -*- coding: utf-8 -*-
"""
Created on Tue Dec 20 13:02:58 2022

@author: lempereu
"""


inp="""Monkey 0:
  Starting items: 99, 67, 92, 61, 83, 64, 98
  Operation: new = old * 17
  Test: divisible by 3
    If true: throw to monkey 4
    If false: throw to monkey 2

Monkey 1:
  Starting items: 78, 74, 88, 89, 50
  Operation: new = old * 11
  Test: divisible by 5
    If true: throw to monkey 3
    If false: throw to monkey 5

Monkey 2:
  Starting items: 98, 91
  Operation: new = old + 4
  Test: divisible by 2
    If true: throw to monkey 6
    If false: throw to monkey 4

Monkey 3:
  Starting items: 59, 72, 94, 91, 79, 88, 94, 51
  Operation: new = old * old
  Test: divisible by 13
    If true: throw to monkey 0
    If false: throw to monkey 5

Monkey 4:
  Starting items: 95, 72, 78
  Operation: new = old + 7
  Test: divisible by 11
    If true: throw to monkey 7
    If false: throw to monkey 6

Monkey 5:
  Starting items: 76
  Operation: new = old + 8
  Test: divisible by 17
    If true: throw to monkey 0
    If false: throw to monkey 2

Monkey 6:
  Starting items: 69, 60, 53, 89, 71, 88
  Operation: new = old + 5
  Test: divisible by 19
    If true: throw to monkey 7
    If false: throw to monkey 1

Monkey 7:
  Starting items: 72, 54, 63, 80
  Operation: new = old + 3
  Test: divisible by 7
    If true: throw to monkey 1
    If false: throw to monkey 3"""

inp="""Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3

Monkey 1:
  Starting items: 54, 65, 75, 74
  Operation: new = old + 6
  Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 0

Monkey 2:
  Starting items: 79, 60, 97
  Operation: new = old * old
  Test: divisible by 13
    If true: throw to monkey 1
    If false: throw to monkey 3

Monkey 3:
  Starting items: 74
  Operation: new = old + 3
  Test: divisible by 17
    If true: throw to monkey 0
    If false: throw to monkey 1"""

buff =  [[99, 67, 92, 61, 83, 64, 98],
 [78, 74, 88, 89, 50],
 [98, 91],
 [59, 72, 94, 91, 79, 88, 94, 51],
 [95, 72, 78],
 [76],
 [69, 60, 53, 89, 71, 88],
 [72, 54, 63, 80]]
 

    

nbItem = [0, 0, 0, 0, 0, 0, 0, 0]

for r in range(1,10001): #21
    print("round: {}".format(r))
    
    # Monkey 0
    for i in range(len(buff[0])):
        n = buff[0].pop(0)*17#//3
        nbItem[0] += 1
        if n%3 == 0:
            buff[4].append(n)
        else:
            buff[2].append(n)
            
    # Monkey 1
    for i in range(len(buff[1])):
        n = (buff[1].pop(0)*11)#//3
        nbItem[1] += 1
        if n%5 == 0:
            buff[3].append(n)
        else:
            buff[5].append(n)
    
    # Monkey 2
    for i in range(len(buff[2])):
        n = (buff[2].pop(0)+4)#//3
        nbItem[2] += 1
        if n%2 == 0:
            buff[6].append(n)
        else:
            buff[4].append(n)
    
    # Monkey 3
    for i in range(len(buff[3])):
        n = (buff[3].pop(0)**2)#//3
        nbItem[3] += 1
        if n%13 == 0:
            buff[0].append(n)
        else:
            buff[5].append(n)
    
    # Monkey 4
    for i in range(len(buff[4])):
        n = (buff[4].pop(0)+7)#//3
        nbItem[4] += 1
        if n%11 == 0:
            buff[7].append(n)
        else:
            buff[6].append(n)
            
    # Monkey 5
    for i in range(len(buff[5])):
        n = (buff[5].pop(0)+8)#//3
        nbItem[5] += 1
        if n%17 == 0:
            buff[0].append(n)
        else:
            buff[2].append(n)
    # Monkey 6
    for i in range(len(buff[6])):
        n = (buff[6].pop(0)+5)#//3
        nbItem[6] += 1
        if n%19 == 0:
            buff[7].append(n)
        else:
            buff[1].append(n)
            
    # Monkey 7
    for i in range(len(buff[7])):
        n = (buff[7].pop(0)+3)#//3
        nbItem[7] += 1
        if n%7 == 0:
            buff[1].append(n)
        else:
            buff[3].append(n)
    
    # end of the round
    #for i in range(4):
    #    nbItem[i] += len(buff[i])
    print(buff)
print(nbItem)
print(sorted(nbItem))
# smaller than 623392 352*1771