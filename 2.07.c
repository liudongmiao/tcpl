/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 02:25:54 PM CST
 * Modified : Wed 08 Aug 2012 07:54:59 PM CST
 */

/*
 * Write a function ``invert(x,p,n)'' that returns ``x'' with the ``n'' bits
 * that begin at position ``p'' inverted (i.e., 1 changed to 0 and vice versa),
 * leaving the others unchanged.
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

unsigned invert(unsigned x, int p, int n)
{
	/*
	unsigned part1 = (x & (~0 << (p + 1)));
	unsigned part2 = (~(x >> (p + 1 - n)) & ~(~0 << n)) << (p + 1 - n);
	unsigned part3 = (x & ~(~0 << (p + 1 - n)));
	return part1 | part2 | part3;
	*/
	return x ^ (~(~0 << n) << (p + 1 - n));
}

int main()
{
	unsigned int x = 0x155; /* 1 0101 0101 */
	int p = 7;
	int n = 4;
	unsigned z = invert(x, p, n);
	unsigned r = 0x1a5; /* 1 1010 0101 */
	printf("x=%x, z=%x, r=%x\n", x, z, r);
	return 0;
}
