#!/usr/bin/python3
import matplotlib.pyplot as plt
import utils

def readFile(filename):
	#of = open("traces/"+filename,"r")
	of = open(filename,"r")
	lines = [i.strip().split() for i in of.readlines()]
	of.close()
	cwnd = []
	time = []
	for line in lines:
		if "cwnd_" in line:
			time.append(float(line[0]))
			cwnd.append(float(line[6]))
	return time, cwnd


def get_time_and_averages(iterations, algorithm):
	time_0 = []
	time_1 = []
	average_cwnd_0 = []
	average_cwnd_1 = []
	for i in range(1, iterations + 1):
		time_0, cwnd_0 = readFile("tcp"+str(i)+"-"+algorithm+"-flow0.tr")
		average_cwnd_0 = utils.add_items(cwnd_0, average_cwnd_0)
		time_1, cwnd_1 = readFile("tcp"+str(i)+"-"+algorithm+"-flow1.tr")
		average_cwnd_1 = utils.add_items(cwnd_1, average_cwnd_1)
	average_cwnd_0 = [i / iterations for i in average_cwnd_0]
	average_cwnd_1 = [i / iterations for i in average_cwnd_1]
	return time_0, average_cwnd_0, time_1, average_cwnd_1

def plot_flows(time_0, average_cwnd_0, time_1, average_cwnd_1, algorithm):
	plt.figure(figsize = [10, 7])
	plt.title(algorithm, fontsize=16)
	plt.plot(time_0, average_cwnd_0, color="b")
	plt.plot(time_1, average_cwnd_1, color="r")
	plt.legend(['Flow1 (delay 5ms)', 'Flow2 (variable delay 5-25ms)'], loc='best')

	plt.xlabel('Time (ms)', fontsize=14) 
	plt.ylabel('CWND', fontsize=14)   
	plt.tight_layout()
	#plt.savefig("img/cwnd/"+algorithm+"_cwnd.png")
	plt.savefig("/home/asad-ali/Problem3/Sample_Python/"+algorithm+"_cwnd.png")
	plt.close()