#Advent 5
import re

"""
			[C]		 [N] [R]	
[J] [T]	 [H]		 [P] [L]	
[F] [S] [T] [B]		 [M] [D]	
[C] [L] [J] [Z] [S]	 [L] [B]	
[N] [Q] [G] [J] [J]	 [F] [F] [R]
[D] [V] [B] [L] [B] [Q] [D] [M] [T]
[B] [Z] [Z] [T] [V] [S] [V] [S] [D]
[W] [P] [P] [D] [G] [P] [B] [P] [V]
 1   2   3   4   5   6   7   8   9 
"""

stack = [['W', 'B', 'D', 'N', 'C', 'F', 'J'],
['P', 'Z', 'V', 'Q', 'L', 'S', 'T'],
['P', 'Z', 'B', 'G', 'J', 'T'],
['D', 'T', 'L', 'J', 'Z', 'B', 'H', 'C'],
['G', 'V', 'B', 'J', 'S'],
['P', 'S', 'Q'],
['B', 'V', 'D', 'F', 'L', 'M', 'P', 'N'],
['P', 'S', 'M', 'F', 'B', 'D', 'L', 'R'],
['V', 'D', 'T', 'R']]

inp="""move 4 from 9 to 6
move 7 from 2 to 5
move 3 from 5 to 2
move 2 from 2 to 1
move 2 from 8 to 4
move 1 from 6 to 9
move 1 from 9 to 4
move 7 from 1 to 2
move 5 from 2 to 3
move 5 from 7 to 4
move 5 from 6 to 3
move 1 from 7 to 6
move 2 from 6 to 9
move 3 from 2 to 4
move 4 from 5 to 6
move 2 from 7 to 3
move 2 from 9 to 3
move 1 from 5 to 2
move 11 from 4 to 3
move 1 from 2 to 9
move 1 from 9 to 3
move 2 from 1 to 6
move 5 from 8 to 5
move 7 from 5 to 4
move 2 from 5 to 6
move 6 from 6 to 4
move 17 from 3 to 4
move 1 from 8 to 3
move 11 from 4 to 7
move 1 from 6 to 4
move 3 from 4 to 2
move 2 from 2 to 6
move 8 from 3 to 1
move 8 from 3 to 9
move 3 from 9 to 6
move 3 from 1 to 3
move 11 from 7 to 5
move 1 from 6 to 4
move 4 from 9 to 6
move 3 from 1 to 4
move 1 from 2 to 3
move 1 from 6 to 9
move 24 from 4 to 9
move 2 from 6 to 5
move 1 from 1 to 2
move 1 from 1 to 3
move 12 from 9 to 6
move 5 from 4 to 2
move 4 from 2 to 3
move 5 from 6 to 3
move 13 from 6 to 7
move 1 from 5 to 6
move 9 from 5 to 3
move 4 from 7 to 5
move 1 from 6 to 1
move 3 from 5 to 1
move 14 from 9 to 4
move 2 from 7 to 9
move 13 from 4 to 9
move 1 from 4 to 7
move 4 from 7 to 9
move 3 from 5 to 1
move 8 from 3 to 9
move 4 from 1 to 4
move 8 from 3 to 7
move 3 from 7 to 6
move 4 from 4 to 2
move 3 from 1 to 9
move 6 from 2 to 6
move 3 from 3 to 1
move 7 from 9 to 7
move 2 from 6 to 5
move 1 from 5 to 3
move 3 from 7 to 5
move 5 from 7 to 4
move 2 from 1 to 4
move 5 from 5 to 9
move 6 from 4 to 1
move 6 from 7 to 8
move 22 from 9 to 3
move 7 from 1 to 8
move 4 from 9 to 6
move 1 from 4 to 5
move 8 from 6 to 4
move 7 from 8 to 1
move 1 from 6 to 4
move 1 from 9 to 4
move 1 from 1 to 2
move 1 from 2 to 5
move 1 from 9 to 8
move 11 from 3 to 7
move 1 from 6 to 2
move 2 from 1 to 5
move 1 from 8 to 2
move 1 from 7 to 8
move 4 from 5 to 7
move 1 from 6 to 9
move 6 from 3 to 1
move 6 from 3 to 1
move 15 from 7 to 5
move 1 from 3 to 1
move 1 from 3 to 6
move 1 from 6 to 8
move 14 from 5 to 1
move 16 from 1 to 3
move 2 from 8 to 9
move 1 from 7 to 4
move 3 from 9 to 8
move 3 from 8 to 7
move 2 from 3 to 5
move 1 from 7 to 1
move 6 from 8 to 5
move 2 from 2 to 9
move 1 from 7 to 2
move 2 from 9 to 2
move 5 from 4 to 7
move 3 from 2 to 7
move 14 from 1 to 5
move 2 from 4 to 7
move 8 from 7 to 6
move 1 from 1 to 5
move 1 from 7 to 4
move 1 from 7 to 5
move 1 from 1 to 8
move 12 from 3 to 4
move 1 from 8 to 7
move 3 from 4 to 1
move 1 from 6 to 2
move 8 from 5 to 2
move 1 from 7 to 6
move 1 from 1 to 7
move 6 from 6 to 2
move 1 from 1 to 2
move 14 from 5 to 7
move 1 from 6 to 4
move 4 from 4 to 7
move 1 from 1 to 6
move 1 from 5 to 6
move 2 from 3 to 1
move 14 from 7 to 5
move 10 from 4 to 7
move 1 from 1 to 9
move 1 from 5 to 9
move 11 from 5 to 1
move 6 from 7 to 6
move 1 from 4 to 6
move 1 from 3 to 7
move 2 from 1 to 5
move 13 from 2 to 1
move 10 from 6 to 7
move 4 from 5 to 2
move 1 from 9 to 1
move 1 from 3 to 6
move 2 from 5 to 2
move 1 from 9 to 3
move 1 from 3 to 1
move 21 from 7 to 5
move 1 from 6 to 4
move 4 from 5 to 1
move 1 from 4 to 1
move 6 from 2 to 3
move 1 from 3 to 6
move 1 from 3 to 8
move 1 from 8 to 7
move 1 from 7 to 3
move 9 from 5 to 3
move 24 from 1 to 4
move 1 from 3 to 7
move 11 from 3 to 8
move 1 from 7 to 3
move 1 from 2 to 4
move 2 from 2 to 1
move 2 from 3 to 5
move 1 from 6 to 5
move 10 from 4 to 6
move 2 from 6 to 4
move 5 from 1 to 2
move 1 from 6 to 7
move 8 from 8 to 6
move 4 from 2 to 7
move 8 from 6 to 7
move 1 from 2 to 8
move 1 from 8 to 3
move 1 from 7 to 4
move 3 from 4 to 1
move 2 from 6 to 7
move 4 from 1 to 9
move 3 from 6 to 7
move 10 from 7 to 4
move 2 from 3 to 9
move 2 from 6 to 9
move 2 from 1 to 8
move 2 from 9 to 5
move 4 from 5 to 6
move 3 from 8 to 1
move 4 from 4 to 8
move 5 from 8 to 4
move 1 from 8 to 2
move 5 from 5 to 9
move 1 from 6 to 1
move 2 from 1 to 7
move 22 from 4 to 8
move 4 from 8 to 7
move 2 from 6 to 7
move 1 from 2 to 6
move 16 from 8 to 9
move 3 from 7 to 4
move 1 from 5 to 9
move 2 from 6 to 7
move 1 from 8 to 2
move 1 from 2 to 3
move 24 from 9 to 3
move 1 from 1 to 7
move 3 from 5 to 1
move 4 from 4 to 6
move 15 from 3 to 6
move 18 from 6 to 2
move 3 from 3 to 2
move 4 from 1 to 6
move 4 from 7 to 3
move 1 from 3 to 9
move 4 from 2 to 1
move 1 from 8 to 7
move 3 from 9 to 6
move 1 from 9 to 3
move 4 from 7 to 3
move 2 from 4 to 2
move 1 from 1 to 2
move 7 from 3 to 5
move 8 from 6 to 1
move 1 from 9 to 2
move 3 from 7 to 5
move 1 from 4 to 8
move 3 from 1 to 7
move 5 from 7 to 6
move 3 from 5 to 2
move 3 from 7 to 3
move 5 from 5 to 9
move 5 from 3 to 6
move 1 from 8 to 3
move 5 from 9 to 7
move 7 from 2 to 4
move 11 from 2 to 7
move 7 from 1 to 6
move 1 from 1 to 9
move 5 from 3 to 6
move 5 from 2 to 1
move 1 from 3 to 9
move 1 from 3 to 7
move 6 from 6 to 2
move 10 from 6 to 7
move 5 from 6 to 7
move 28 from 7 to 8
move 2 from 9 to 1
move 1 from 6 to 3
move 4 from 7 to 5
move 1 from 3 to 6
move 7 from 2 to 7
move 6 from 7 to 3
move 1 from 5 to 9
move 1 from 6 to 2
move 1 from 7 to 3
move 1 from 9 to 1
move 4 from 5 to 2
move 5 from 3 to 5
move 2 from 2 to 8
move 4 from 4 to 7
move 1 from 4 to 7
move 2 from 3 to 6
move 5 from 7 to 1
move 2 from 5 to 8
move 2 from 5 to 8
move 2 from 5 to 3
move 2 from 3 to 1
move 2 from 6 to 7
move 31 from 8 to 3
move 2 from 8 to 5
move 2 from 7 to 4
move 7 from 1 to 4
move 2 from 5 to 1
move 3 from 2 to 8
move 2 from 4 to 6
move 3 from 1 to 2
move 6 from 4 to 8
move 1 from 1 to 8
move 1 from 6 to 5
move 11 from 8 to 9
move 1 from 6 to 8
move 1 from 4 to 1
move 1 from 8 to 7
move 1 from 5 to 8
move 3 from 2 to 1
move 2 from 4 to 3
move 1 from 8 to 1
move 7 from 3 to 6
move 12 from 3 to 2
move 1 from 7 to 9
move 4 from 6 to 1
move 1 from 6 to 3
move 12 from 9 to 3
move 1 from 6 to 4
move 1 from 1 to 7
move 1 from 4 to 1
move 1 from 7 to 2
move 1 from 6 to 5
move 1 from 5 to 6
move 5 from 3 to 1
move 1 from 6 to 4
move 7 from 2 to 1
move 3 from 2 to 6
move 1 from 4 to 5
move 3 from 3 to 2
move 4 from 2 to 8
move 1 from 6 to 4
move 1 from 4 to 9
move 1 from 5 to 1
move 11 from 1 to 5
move 10 from 1 to 8
move 2 from 6 to 4
move 1 from 2 to 9
move 1 from 2 to 4
move 18 from 3 to 5
move 4 from 1 to 4
move 3 from 1 to 2
move 14 from 8 to 5
move 2 from 2 to 6
move 1 from 3 to 2
move 2 from 2 to 7
move 3 from 4 to 1
move 2 from 4 to 3
move 2 from 3 to 4
move 2 from 6 to 9
move 1 from 7 to 1
move 3 from 1 to 4
move 4 from 9 to 7
move 31 from 5 to 2
move 25 from 2 to 4
move 13 from 4 to 2
move 10 from 2 to 3
move 2 from 5 to 7
move 5 from 2 to 9
move 7 from 5 to 7
move 5 from 7 to 4
move 1 from 5 to 8
move 2 from 7 to 3
move 11 from 4 to 8
move 1 from 7 to 3
move 1 from 1 to 4
move 2 from 5 to 3
move 3 from 2 to 9
move 8 from 9 to 6
move 10 from 8 to 2
move 5 from 3 to 2
move 1 from 7 to 3
move 3 from 7 to 3
move 15 from 2 to 1
move 11 from 1 to 3
move 1 from 8 to 2
move 8 from 6 to 5
move 1 from 2 to 6
move 1 from 6 to 1
move 12 from 3 to 7
move 1 from 2 to 9
move 2 from 4 to 1
move 3 from 1 to 8
move 1 from 8 to 7
move 3 from 3 to 4
move 1 from 4 to 7
move 15 from 7 to 9
move 1 from 7 to 5
move 4 from 1 to 8
move 6 from 8 to 6
move 1 from 6 to 2
move 5 from 5 to 1
move 2 from 6 to 8
move 1 from 2 to 7
move 1 from 8 to 2
move 1 from 7 to 1
move 1 from 5 to 8
move 6 from 3 to 1
move 4 from 3 to 8
move 7 from 8 to 5
move 1 from 2 to 4
move 2 from 4 to 2
move 3 from 6 to 4
move 5 from 9 to 3
move 4 from 1 to 4
move 10 from 5 to 9
move 8 from 1 to 7
move 1 from 2 to 1
move 1 from 1 to 9
move 20 from 9 to 2
move 12 from 2 to 3
move 17 from 4 to 3
move 6 from 7 to 2
move 5 from 3 to 8
move 20 from 3 to 5
move 2 from 9 to 4
move 3 from 3 to 1
move 1 from 7 to 1
move 6 from 3 to 6
move 4 from 2 to 3
move 4 from 5 to 3
move 1 from 1 to 9
move 6 from 6 to 1
move 3 from 8 to 4
move 1 from 9 to 8
move 2 from 2 to 1
move 3 from 3 to 2
move 1 from 3 to 6
move 1 from 7 to 4
move 3 from 3 to 6
move 6 from 1 to 5
move 9 from 2 to 4
move 3 from 2 to 5
move 2 from 6 to 5
move 16 from 4 to 8
move 18 from 8 to 6
move 1 from 4 to 5
move 2 from 6 to 7
move 4 from 1 to 7
move 22 from 5 to 6
move 1 from 4 to 9
move 4 from 7 to 6
move 11 from 6 to 5
move 9 from 5 to 2
move 2 from 2 to 3
move 2 from 7 to 2
move 1 from 1 to 7
move 9 from 6 to 2
move 1 from 5 to 1
move 1 from 8 to 9
move 18 from 6 to 8
move 1 from 7 to 4
move 4 from 5 to 1
move 2 from 5 to 2
move 2 from 2 to 5
move 1 from 9 to 5
move 1 from 5 to 9
move 1 from 9 to 1
move 1 from 9 to 2
move 1 from 4 to 8
move 4 from 1 to 4
move 2 from 6 to 5
move 1 from 1 to 9
move 3 from 6 to 7
move 1 from 6 to 9
move 1 from 9 to 8
move 2 from 5 to 9
move 3 from 3 to 5
move 7 from 2 to 3
move 1 from 1 to 3
move 2 from 5 to 9
move 1 from 5 to 7
move 10 from 8 to 3
move 10 from 8 to 9
move 3 from 4 to 3
move 9 from 2 to 1
move 4 from 9 to 6
move 5 from 1 to 9
move 2 from 5 to 9
move 1 from 6 to 4
move 4 from 7 to 2
move 7 from 2 to 9
move 3 from 6 to 8
move 1 from 1 to 3
move 2 from 8 to 5
move 1 from 8 to 1
move 18 from 3 to 6
move 15 from 9 to 2
move 8 from 9 to 1
move 2 from 9 to 2
move 2 from 4 to 9
move 2 from 9 to 7
move 12 from 6 to 3
move 7 from 1 to 7
move 12 from 2 to 5
move 7 from 3 to 2
move 4 from 3 to 4
move 2 from 7 to 6
move 7 from 7 to 8
move 1 from 4 to 2
move 4 from 1 to 8
move 5 from 3 to 1
move 9 from 8 to 3
move 1 from 8 to 7
move 2 from 1 to 2
move 4 from 6 to 7
move 11 from 2 to 5
move 2 from 4 to 6
move 1 from 8 to 2
move 7 from 3 to 2
move 1 from 2 to 4
move 4 from 6 to 1
move 7 from 5 to 8
move 2 from 3 to 1
move 7 from 2 to 3
move 6 from 5 to 1
move 1 from 4 to 2
move 8 from 1 to 6
move 3 from 2 to 9"""

"""
	[D]	
[N] [C]	
[Z] [M] [P]
 1   2   3
"""
#stack=[['Z', 'N'],['M', 'C', 'D'], ['P']]

#inp=
"""move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2"""

#Part 1
cc = 0
for i in inp.split("\n"):
	reg = re.search(r"^move ([0-9]+) from ([0-9]+) to ([0-9]+)$", i)
	a, b, c = int(reg.group(1)),  int(reg.group(2))-1, int(reg.group(3))-1
	print(a, b, c)
	for i in range(a):
		stack[c].append(stack[b].pop())
print(stack)
ans= ""
for i in stack:
	if len(i)>0:
		ans += i[-1]
print("Ans: {}".format(ans))

stack = [['W', 'B', 'D', 'N', 'C', 'F', 'J'],
['P', 'Z', 'V', 'Q', 'L', 'S', 'T'],
['P', 'Z', 'B', 'G', 'J', 'T'],
['D', 'T', 'L', 'J', 'Z', 'B', 'H', 'C'],
['G', 'V', 'B', 'J', 'S'],
['P', 'S', 'Q'],
['B', 'V', 'D', 'F', 'L', 'M', 'P', 'N'],
['P', 'S', 'M', 'F', 'B', 'D', 'L', 'R'],
['V', 'D', 'T', 'R']]

#Part 2
cc = 0
for i in inp.split("\n"):
	reg = re.search(r"^move ([0-9]+) from ([0-9]+) to ([0-9]+)$", i)
	a, b, c = int(reg.group(1)),  int(reg.group(2))-1, int(reg.group(3))-1
	print(a, b, c)
	l = []
	for k in range(a):
		l.append(stack[b].pop())
	for k in range(a):
		stack[c].append(l.pop())
print(stack)
ans= ""
for i in stack:
	if len(i)>0:
		ans += i[-1]
print("Ans: {}".format(ans))