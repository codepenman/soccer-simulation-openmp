import Main

runtimes = []
for i in xrange(100):
	runtimes.append(Main.play(2))

runtimesWith4Threads = []
for i in xrange(100):
	runtimesWith4Threads.append(Main.play(4))

sum = 0
with open("some.csv", "w") as file:
	for runtime in runtimes:
		file.write(str(runtime))
		file.write(",")
		sum = sum + runtime
file.close()

print "Average with 2 threads: ", (sum/len(runtimes))

sum = 0
with open("runtime4.csv", "w") as file:
	for runtime in runtimesWith4Threads:
		file.write(str(runtime))
		file.write(",")
		sum = sum + runtime

print "Average with 4 threads: ", (sum/len(runtimesWith4Threads))
