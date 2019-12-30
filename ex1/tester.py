import os, shutil
from termcolor import colored

IO_FOLDER = "./Input_Outpuf_Files"
BIN_FILE = "./bin/ex1"
ERROR_1 = "Reason: Bad Positioning input file"
ERROR_2 = "Reason: Bad Moves input file"

def main():
	for folder in os.listdir(IO_FOLDER):
		for sub_folder in os.listdir("{}/{}".format(IO_FOLDER,folder)):
			test_path = "{}/{}/{}".format(IO_FOLDER,folder,sub_folder)
			print test_path
			try:
				shutil.copy2("{}/player1.rps_board".format(test_path), "./")
				shutil.copy2("{}/player1.rps_moves".format(test_path), "./")
				shutil.copy2("{}/player2.rps_board".format(test_path), "./")
				shutil.copy2("{}/player2.rps_moves".format(test_path), "./")
			except:
				print "Failed to copy files from {}".format(test_path)
				continue
			os.system(BIN_FILE)
			try:
				with open("{}/rps.output".format(test_path), "r") as infile:
					origfile = infile.read().splitlines()
			except:
				with open("{}/rps.expected".format(test_path), "r") as infile:
					origfile = infile.read().splitlines()
			with open("./rps.output", "r") as infile:
				newfile = infile.read().splitlines()
			if (origfile[0] != newfile[0]):
				print colored("Wrong winner", "red")
				print "\nGood: {}\nOurs: {}\n".format(origfile[0],newfile[0])
			elif (origfile[1] != newfile[1]):
				print colored("Wrong reason", "red")
				print "\nGood: {}\nOurs: {}\n".format(origfile[1],newfile[1])
			elif (origfile != newfile):
				if ((newfile[1][:len(ERROR_1)] == ERROR_1)or(newfile[1][:len(ERROR_2)] == ERROR_2)):
					print colored("Wrong board ignored", "yellow")
				else:
					print colored("Wrong board", "red")
			else:
				print colored("OK", "green")
	os.remove("./player1.rps_board")
	os.remove("./player1.rps_moves")
	os.remove("./player2.rps_board")
	os.remove("./player2.rps_moves")
	os.remove("./rps.output")

if __name__ == "__main__":
	main()
