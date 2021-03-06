'''
	https://www.interviewbit.com/problems/spiral-order-matrix-i/
   Print 2D array of m x n, in a spiral order
'''


'''
In an mxn matrix,

Spiral moves 
   Right: n steps,  (starting at 0,0, keep row fixed)
   Down: m-2 steps, (keep column fixed at (n-1))
   Left: n steps, (keep row fixed from last time, columns: n-1 to 0)
   Up: m-2 steps,   (keep column fixed from last time at 0, rows: m-1 to 0)
   
   then repeat with inner rect/square, 
   (startrow, startcol) += 1
   n -= 2, m -= 2
'''

def spiral_print(arr, m, n):
	def spiral_print_helper_r(arr, startrow, startcol, m, n, spiral_array):
		if m <=0 or n <=0:
			return spiral_array

		# Move right from startcol, n steps, keep row fixed at startrow
		i = startcol
		for i in xrange(i, startcol+n):
			spiral_array.append(arr[startrow][i])

		j = startrow+1
		# move down from startrow+1, m-2 steps, keep column fixed from last time
		for j in range(j, startrow+1+m-2):
			spiral_array.append(arr[j][i])

		# if the 2D array has only one row, then
		# the left directional print has no meaning
		# as the initial right directional print would have covered this.
		if m > 1:
			k = startcol+n-1
			# move left from current row, n steps, keep row fixed from last time + 1
			for k in range(k, startcol-1, -1):
				spiral_array.append(arr[startrow+m-2+1][k])

		# if the 2D array has only one column, then
		# the up directional print has no meaning`
		# as the initial down directional print would have covered this.
		if n > 1:
			# move up from current col, m-2 steps, keep column fixed from last time
			for l in range(startrow+m-2, startrow, -1):
				spiral_array.append(arr[l][startcol])

		# Outer rectangle complete, Now process the inner rectangle as a spiral
		return spiral_print_helper_r(arr, startrow+1, startcol+1, m-2, n-2, spiral_array)


	if arr == [] or arr[0] == []:
		return []

	# call the helper function to print the array in spiral order
	return spiral_print_helper_r(arr, 0, 0, m, n, [])



assert spiral_print([], 0, 0) == []
assert spiral_print([[]], 1, 0) == []

a = [
		[1, 2, 3],
		[4, 5, 6],
		[7, 8, 9],
	]
assert(spiral_print(a, 3, 3) == [1,2,3,6,9,8,7,4,5])


a = [[1]]
assert spiral_print(a, 1, 1) == [1]

a = [[1,2,3]]
assert spiral_print(a, 1, 3) == [1,2,3]

a = [[1], [2], [3]]
assert spiral_print(a, 3, 1) == [1,2,3]

a = [[1], [2]]
assert spiral_print(a, 2, 1) == [1,2]

a = [[1,2,3], [4,5,6]]
assert spiral_print(a, 2, 3) == [1,2,3,6,5,4]


a = [
		[1, 2, 3],
		[5, 6, 7],
		[9, 10, 11],
		[13, 14, 15],
	]

assert(spiral_print(a, len(a), len(a[0]))  == [1, 2, 3, 7, 11, 15, 14, 13, 9, 5, 6, 10])



a = [
		[1, 2, 3],
		[4, 5, 6],
		[7, 8, 9],
	]
assert(spiral_print(a, 3, 3) == [1,2,3,6,9,8,7,4,5])

assert(spiral_print(
	    [
			"abcde",
			"fghij",
			"klmno",
			"pqrst",
			"uvwxy",
		], 
		5, 5) == ['a', 'b', 'c', 'd', 'e', 'j', 'o', 't', 'y', 'x', 'w', 'v', 'u', 'p', 'k', 'f', 'g', 'h', 'i', 'n', 's', 'r', 'q', 'l', 'm'])

