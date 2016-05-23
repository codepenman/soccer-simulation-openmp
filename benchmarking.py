import Main
import time


#Heating the cache
for i in xrange(100):
	Main.play(2)

runtimes = []
for i in xrange(100):
	runtimes.append(Main.play(2))

time.sleep(30)

# #Heating the cache
# for i in xrange(100):
# 	Main.play(4)

# runtimesWith4Threads = []
# for i in xrange(100):
# 	runtimesWith4Threads.append(Main.play(4))

# time.sleep(30)

# #Heating the cache
# for i in xrange(100):
# 	Main.play(8)

# runtimesWith8Threads = []
# for i in xrange(100):
# 	runtimesWith8Threads.append(Main.play(8))

# time.sleep(30)

# #Heating the cache
# for i in xrange(100):
# 	Main.play(16)

# runtimesWith16Threads = []
# for i in xrange(100):
# 	runtimesWith16Threads.append(Main.play(16))


# sum = 0
# with open("some.csv", "w") as file:
# 	for runtime in runtimes:
# 		file.write(str(runtime))
# 		file.write(",")
# 		sum = sum + runtime
# file.close()

# print "Average with 2 threads: ", (sum/len(runtimes))

# sum = 0
# with open("runtime4.csv", "w") as file:
# 	for runtime in runtimesWith4Threads:
# 		file.write(str(runtime))
# 		file.write(",")
# 		sum = sum + runtime

# print "Average with 4 threads: ", (sum/len(runtimesWith4Threads))

with open("serial.csv", "w") as file:
	for i in xrange(100):
		file.write(str(i))
		file.write(",")
		file.write(str(runtimes[i]))
		# file.write(",")
		# file.write(str(runtimesWith4Threads[i]))
		# file.write(",")
		# file.write(str(runtimesWith8Threads[i]))
		# file.write(",")
		# file.write(str(runtimesWith16Threads[i]))
		file.write("\n")
	file.close()