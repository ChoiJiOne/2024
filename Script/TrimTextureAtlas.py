import json
import sys
import os

if __name__ == '__main__':
    # 명령행 인수 검사.
    if len(sys.argv) != 2:
        print("\n>> Invalid command line argument! <<")
        print("Command syntax: {0} <filename>\n".format(sys.argv[0]))
        sys.exit(0)

    # 파일 유효성 검사.
    target_file_path = sys.argv[1]
    if not os.path.exists(target_file_path):
        print("\n>> No file found at '{0}'\n".format(target_file_path))