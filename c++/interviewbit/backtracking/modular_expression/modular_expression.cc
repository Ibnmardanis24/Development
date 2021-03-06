/*
https://www.interviewbit.com/problems/modular-expression/

Modular Expression

Implement pow(a, b) % c.

In other words, given a, b and c,
find (a^b)%c.

Input : a = 2, b = 3, c = 3
Return : 2 
2^3 % 3 = 8 % 3 = 2
*/

/**
Solution Outline:
	(axb) % c == (a%c * b%c) % c
	=> 
	  a^b % c ==
	   [{a^(b/2) % c} * {a^(b/2) % c}] % c  if b is even
	   [{a^(b/2) % c} * {a^(b/2) % c} * a%c }] % c  if b is odd
	   1 if b == 0


Sample run:
	2^5 % 13
	== {2^2 % 13 * 2^2 % 13 * 2%13} % 13
	== { {2%13 * 2%13}%13 * {2%13 * 2%13}%13 * 2%13 } % 13
	== { 4 * 4 * 2} % 13
	== { { 16 % 13} * {2} } % 13
	== { 3 * 2} % 13
	== 6
*/

#include <cassert>

class Solution {
public:
	int mod(int a, int b, int c) {
		if (a == 0)
			return 0;

		if (b == 0)
			return 1;

		long long x = this->mod(a, b>>1, c);
		x = (x * x) % c;
		if ((b & 1) == 1) {
			// add +c incase a is -ve
			return (x * a%c + c) % c;
		}

		return x;
	}
};



int
main(void)
{
	Solution s;

	assert(s.mod(2, 3, 3) == 2);
	assert(s.mod(2, 3, 5) == 3);
	assert(s.mod(2, 5, 13) == 6);
	assert(s.mod(0, 5, 13) == 0);
	assert(s.mod(-1, 1, 20) == 19);

	return 0;
}

