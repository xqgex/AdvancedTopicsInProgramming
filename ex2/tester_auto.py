import subprocess
from termcolor import colored

BIN_FILE = ["./bin/ex2","auto-vs-auto"]
GOOD_MSGS = ["Reason: All flags of the opponent are captured", "Reason: All moving PIECEs of the opponent are eaten", "Reason: A tie - all flags are eaten by both players in the position files"]
GOOD_OUTPUT = "Done, Check the output file for more information"
NOT_AN_ERROR = "Reason: A tie - both Moves input files done without a winner"
EXTRA_OUTPUT = ["Both players don't have any more moveable pieces\n", "ERROR: Game ended after 100 moves without a fight\n"]

def main():
	for counter in range(10000):
		if counter % 100 == 0:
			print counter
		popen = subprocess.Popen(BIN_FILE, stdout=subprocess.PIPE)
		popen.wait()
		output = popen.stdout.read().strip()
		with open("./rps.output", "r") as infile:
			result = infile.read().splitlines()
		if not result:
			print "############# Error (Empty) #############"
			print output
			pass
			exit(0)
		elif result[1] not in GOOD_MSGS:
			if ((result[1] != NOT_AN_ERROR)or( (output != EXTRA_OUTPUT[0]+GOOD_OUTPUT)and(output != EXTRA_OUTPUT[1]+GOOD_OUTPUT) )):
				print "############# Error (File) #############"
				print result
				print output
				exit(0)
		elif output != GOOD_OUTPUT:
			print "############# Error (stdout) #############"
			print result
			print output
			exit(0)
	print "Done"

if __name__ == "__main__":
	main()
