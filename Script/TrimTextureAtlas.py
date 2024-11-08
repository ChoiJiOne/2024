import json
import sys
import os

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("\n>> Invalid command line argument! <<")
        print("Command syntax: {0} <filename>\n".format(sys.argv[0]))
        sys.exit(0)