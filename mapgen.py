#python map generator
from random import randint

x = 10
y = 10
force = 1000 

for x in range(10):
	for y in range(10):
		print "%d %d %d" % (x , y , randint(0,force))

