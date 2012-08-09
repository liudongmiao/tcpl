/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 02:10:05 PM CST
 * Modified : Wed 08 Aug 2012 07:55:04 PM CST
 */

/*
 * Write a function ``setbits(x,p,n,y)'' that returns ``x'' with the ``n'' bits
 * that begin at position ``p'' set to the rightmost ``n'' bits of ``y'',
 * leaving the other bits unchanged.
 */

#include <stdio.h>

/*
 *    --> p + 1
 *    |
 *    |p
 * ....p...n....
 *         |
 *         |
 *         --> p - (n - 1) = p + 1 - n
 *
 */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned part1 = (x & (~0 << (p + 1)));
	unsigned part2 = (y & ~(~0 << n)) << (p + 1 - n);
	unsigned part3 = (x & ~(~0 << (p + 1 - n)));
	return part1 | part2 | part3;
}

int main()
{
	unsigned int x = 0x3ff; /* 11 1111 1111 */;
	int p = 7;
	int n = 4;
	unsigned int y = 0x15; /* 1 0101 */
	unsigned int z = setbits(x, p, n, y);
	unsigned int r = 0x35f; /* 11 0101 1111 */
	printf("x=%x, p=%d, n=%d, y=%x, z=%x, r=%x\n", x, p, n, y, z, r);
	return 0;
}
