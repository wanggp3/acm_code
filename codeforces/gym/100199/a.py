#label : number theory
from fractions import gcd
import sys
fin = open("china.in", "r")
fout = open("china.out", "w")
a, = map(int, fin.readline().split())
b = a / 2
while(True):
    if (gcd(a, b) == 1):
        break
    b = b - 1
fout.write(str(b))
