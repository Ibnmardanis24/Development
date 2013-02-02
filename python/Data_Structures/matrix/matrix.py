'''
	Implement Matrix Operations for use with hill-cipher and other matrix based crypto-primitives
'''

class Matrix:
	def __init__(self, rows=None, cols=None, matrix=None):
		self.rows = rows
		self.cols = cols
		self.matrix = []

		# If the row is not specified, treat it as an empty matrix
		if not rows:
			self.rows = self.cols = 0
			return
	
		# When column is not specified, Create a square matrix with row x row dimensions
		if not cols: # Square matrix
			self.cols = rows

		# No contents specified for matrix OR the input matrix is not a list
		if (not matrix) or (not isinstance(matrix, list)):
			return
		
		if isinstance(matrix[0], list):	# We have a proper 2D list
			self.matrix = matrix
		else: # it's a flattened 1D list
			# Not enough elements in the specified matrix
			if len(matrix) != self.rows*self.cols:
				return

			# Use list comprehension to 'fold' into a 2D list
			# [matrix[0:cols], matrix[cols:2*cols], ....]
			self.matrix = [[matrix[i:i+self.cols] for i in range(0, self.rows*self.cols, self.cols)]

	
	# Check if the matrix is empty
	def empty(self):
		return (not self.matrix)


	# Return a deep copy of the current matrix
	def copy(self):
		return Matrix(self.rows, self.cols, self.matrx[:])


	# Return a matrix constructed from a list (1d or 2d)
	@classmethod
	def fromList (cls, rows=None, cols=None, mlist=None):
		return cls(rows, cols, mlist)

	
	# Return a matrix constructed from a list of tuples
	@classmethod
	def fromListOfTuples(cls, listOfTuples):
		# TODO: Implement 
		# (Tuples don't need explicit rows/colums.. Get it from len)
		return None 


	# Prepare formatted string for print()
	def __str__(self):
		return str(self.rows) + "x" + str(self.cols) + \
				": " + str(self.matrix)

	
	# Check if two matrices are identical
	def __eq__(self, other):
		# If we are comparing against another matrix, compare rows, cols and elements in the matrix
		if isinstance(other, Matrix):
			if (self.rows != other.rows) or (self.cols != other.cols):
				return False
			return self.matrix == other.matrix	

		# If we are comparing against another list (assumed to be 2D), compare only the elements in the matrix
		if isinstance(other, list):
			return self.matrix == other


	# Verify Compatibility for addition/subtraction
	@staticmethod
	def add_compatible(m1, m2):
		# Matrix addition is not defined if the rows and columns don't match
		if (m1.rows != m2.rows or m1.cols != m2.cols):
			return False
		
		return True

	
	# Helper function to add or subtract 2 matrices
	def __add_or_sub__ (self, other, addsubfn)
		# TODO: Use exceptions for corner conditions and cleaner code

		if self.empty() or other.empty():
			return None

		# Check compatibility before adding/subtracting
		if not Matrix.add_compatible(self, other):
			return None

		# Add/subtract the elements from the rhs matrix
		result_matrix[i][j] = [ [addsubfn(a[i][j], b[i][j]) for j in range(self.cols)] for i in range(self.rows) ]

		return result_matrix


	# Add 2 matrices
	def __add__ (self, other):
		return __add_or_sub__ (self, other, int.__add__) # Pass integer addition function to add/sub


	# Subtract 2 matrices
	def __sub__(self, other):
		return __add_or_sub__ (self, other, int.__sub__) # Pass integer subtraction function to add/sub


	# Calculate dot-product of a matrix (Scalar multiplication)
	def dot_product(self, multiplier):
		return [ [a[i][j]*multiplier for j in range(self.cols)] for i in range(self.rows) ]


	# Verify Compatibility for vector product
	@staticmethod
	def vector_prod_compatible(m1, m2):
		# Matrix multiplication is only defined if the columns of lhs matrix == rows of rhs matrix
		return (m1.cols == m2.rows):

	
	# Calculate vector product of two matrices (Cross-product)
	def vector_product(self, other):
		if not vector_prod_compatible(self, other):
			return None

		# A:mxp, B:pxn, A.B: mxn
		# Create a zero-matrix of mxn dimensions
		prod_matrix = Matrix(self.rows, other.cols, [0]*(self.rows * other.cols))

		for i in range(0, prod_matrix.rows):
			for j in range(0, prod_matrix.cols):
				# set matrix[i][j] = 0 in product matrix
				prod_matrix[i][j] = 0
				for k in range(0, self.cols):
					prod_matrix.matrix[i][j] += (self.matrix[i][k] * other.matrix[k][j])

		return prod_matrix


	# Multiply 2 matrices
	# Dot product if rhs is an integer
	# Vector product, otherwise
	def __mul__(self, other):
		if self.empty() or other.empty():
			return None

		if isinstance(other, int):
			return self.dot_product(other)
		elif isinstance(other, Matrix):
			return self.vector_product(other)


	# Check if current matrix is an Identity Matrix
	def isIdentity(self):
		# All Identity matrices are square matrices
		if self.cols != self.rows:
			return False

		for i in range(0, self.rows):
			for j in range(0, self.rows):
				if (i != j):
					if (self.matrix[i][j] != 0):
						return False
				else:
					if (self.matrix[i][i] != 1):
						return False

		return True

	@staticmethod
	def getIdentityMatrix(order):
		iMatrix = Matrix(order)

		for i in range(0, order):	# Prepare the rows
			iMatrix.matrix.append([])
			for j in range(0, order):
				iMatrix.matrix[i].append(0)	# Initialize all columns of current row to zero
		
		for i in range(0, order):
			iMatrix.matrix[i][i] = 1

		return iMatrix

	# Transpose a matrix, rows <-> columns
	def transpose(self):
		tm = Matrix(self.cols, self.rows)

		for i in range(0, tm.rows):
			tm.matrix.append([])	# Prepare the rows
			for j in range(0, tm.cols):
				tm.matrix[i].append(self.matrix[j][i])

		return tm

