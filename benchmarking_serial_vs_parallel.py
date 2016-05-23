import Main
import time


loopCount = 10
#Heating the cache
for i in xrange(100):
	Main.init(loopCount)
	Main.play(2)

runtimesWith10 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith10.append(Main.play(2))
time.sleep(5)


loopCount = 100
#Heating the cache
for i in xrange(100):
	Main.init(loopCount)
	Main.play(2)

runtimesWith100 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith100.append(Main.play(2))
time.sleep(5)

loopCount = 1000
#Heating the cache
for i in xrange(100):
	Main.init(loopCount)
	Main.play(2)

runtimesWith1000 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith1000.append(Main.play(2))
time.sleep(5)

loopCount = 10000
#Heating the cache
for i in xrange(100):
	Main.init(loopCount)
	Main.play(2)

runtimesWith10000 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith10000.append(Main.play(2))
time.sleep(5)


loopCount = 100000
#Heating the cache
for i in xrange(100):
	Main.init(loopCount)
	Main.play(2)

runtimesWith100000 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith100000.append(Main.play(2))
time.sleep(5)

loopCount = 1000000
#Heating the cache
for i in xrange(10):
	Main.init(loopCount)
	Main.play(2)

runtimesWith1000000 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith1000000.append(Main.play(2))
time.sleep(5)

loopCount = 1000000
#Heating the cache
for i in xrange(10):
	Main.init(loopCount)
	Main.play(2)

runtimesWith10000000 = []
for i in xrange(100):
	Main.init(loopCount)
	runtimesWith10000000.append(Main.play(2))

with open("parallel_varing_time.csv", "w") as file:
	file.write("id, 10, 100, 1000, 10000, 100000, 1000000, 10000000\n")

	for i in xrange(100):
		file.write(str(i))
		file.write(",")
		file.write(str(runtimesWith10[i]))
		file.write(",")
		file.write(str(runtimesWith100[i]))
		file.write(",")
		file.write(str(runtimesWith1000[i]))
		file.write(",")
		file.write(str(runtimesWith10000[i]))
		file.write(",")
		file.write(str(runtimesWith100000[i]))
		file.write(",")
		file.write(str(runtimesWith1000000[i]))
		file.write(",")
		file.write(str(runtimesWith10000000[i]))
		file.write(",")
		# file.write(str(runtimesWith4Threads[i]))
		# file.write(",")
		# file.write(str(runtimesWith8Threads[i]))
		# file.write(",")
		# file.write(str(runtimesWith16Threads[i]))
		file.write("\n")
	file.close()