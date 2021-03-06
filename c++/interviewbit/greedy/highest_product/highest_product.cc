/**
https://www.interviewbit.com/problems/highest-product/

Highest Product


Given an array A, of N integers A.
Return the highest product possible by multiplying 3 numbers from the array.
NOTE: Solution will fit in a 32-bit signed integer.


Input Format:
The first and the only argument is an integer array A.

Output Format:
Return the highest possible product.

Constraints:
1 <= N <= 5e5

Example:
Input 1:
A = [1, 2, 3, 4]

Output 1:
24

Explanation 1:
2 * 3 * 4 = 24

Input 2:
A = [0, -1, 3, 100, 70, 50]

Output 2:
350000

Explanation 2:
70 * 50 * 100 = 350000
*/



/**
Solution Outline:
	1. The 3 highest product is the product of the biggest 3 numbers in A (if all of A is +ve).
		If A contains negative numbers, then it could be maximum( s1*s2*c, a*b*c)
			where s1, s2 are the smallest numbers in A; m1,m2,m3 are the 3 biggest numbers in A, a<=b<=c , s1 <= s2
	2. We can either sort A to find s1,s2, a,b,c and return the max of these products.
		OR compute s1,s2, a,b,c in a single pass
*/

#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>

class Solution
{
	public:
		int find_highest_triplet_product(std::vector<int> &A) {
			if (!A.size())
				return 0;

			if (A.size() < 4) {
				return std::accumulate(
						A.begin(),
						A.end(),
						1,
						[](int a, int b){ return (a*b); }
						);
			}

			int max_element = std::accumulate(
						A.begin(),
						A.end(),
						*A.begin(),
						[](int a, int b){ return std::max(a, b); }
						);

			int min_element = std::accumulate(
						A.begin(),
						A.end(),
						*A.begin(),
						[](int a, int b){ return std::min(a, b); }
						);

			int s1, s2, a, b, c;

			s1 = s2 = max_element;
			a = b = c = min_element;
			for (auto x : A) {
				if (x < s1) {
					/** replacing s1, move previous s1 to s2 */
					s2 = s1;
					s1 = x;
				} else if (x < s2) {
					s2 = x;
				}

				if (x > c) {
					/** replacing c, move previous c to b, and b to a */
					a = b;
					b = c;
					c = x;
				} else if (x > b) {
					/** replacing b, move previous b to a */
					a = b;
					b = x;
				} else if (x > a) {
					a = x;
				}
			}

			return std::max(s1*s2*c, a*b*c);
		}
};


int
main(void)
{
	Solution s;
	{
		std::vector<int> v = {1, 2};
		assert(s.find_highest_triplet_product(v) == 2);
	}
	{
		std::vector<int> v = {-1, 2, 3, 1};
		assert(s.find_highest_triplet_product(v) == 6);
	}
	{
		std::vector<int> v = {1, -4, -5, -4};
		assert(s.find_highest_triplet_product(v) == 20);
	}
	{
		std::vector<int> v = {1, -4, 5, 2, 3};
		assert(s.find_highest_triplet_product(v) == 30);
	}
	{
		std::vector<int> v = {1, 2, 2, 2, 1};
		assert(s.find_highest_triplet_product(v) == 8);
	}
	return 0;
}
