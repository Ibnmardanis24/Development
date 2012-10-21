from MD5 import MD5

def run_test (inText):
	inText = map( lambda x: ord(x), inText )
	md = MD5()
	md.update(inText, len(inText))
	md.finish()
	print md

def runTestCases ():
	test_inputs = [ "", "a", "abc", "message digest", "abcdefghijklmnopqrstuvwxyz", \
					"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", \
					"12345678901234567890123456789012345678901234567890123456789012345678901234567890", \
					"The quick brown fox jumps over the lazy dog" \
					] 

	for i in test_inputs:
		run_test (i)


runTestCases()


'''
MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") =
d174ab98d277d9f5a5611c2c9f419d9f
MD5 ("12345678901234567890123456789012345678901234567890123456789012345678901234567890") = 57edf4a22be3c955ac49da2e2107b67a
MD5 ("The quick brown fox jumps over the lazy dog"): 9e107d9d372bb6826bd81d3542a419d6
'''


