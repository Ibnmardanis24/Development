#!/usr/bin/python

import sys

def jolly(list, n):
	diffList = []
	diffListLen = 0
	for i in range(0, n-1):
		currdiff = abs(list[i] - list[i+1])
		if (diffList.count(currdiff) == 0):
			diffList.append(currdiff)
			diffListLen = diffListLen + 1

	diffList.sort()
	for i in range(0, diffListLen-1):
		if (diffList[i] != (i+1)):
			return False
	return True

inputList = []
for line in sys.stdin.readlines():
	strLine = line[:-1].split(" ")
	currline = []
	for i in strLine:
		currline.append(int(i))
	currline.pop(0)
	inputList.append(currline)

for line in inputList:
	if (jolly(line, len(line))):
		print 'Jolly'
	else:
		print 'Not Jolly'
