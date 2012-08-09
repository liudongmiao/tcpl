/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 02:27:50 PM CST
 * Modified : Thu 09 Aug 2012 09:31:53 AM CST
 */

/*
 * Write a function ``rightrot(x,n)'' that returns the value of the integer
 * ``x'' rotated to the right by ``n'' positions.
 */

#include <stdio.h>

/*
 * ......nabcde
 * nabcde......
 *            |
 *            --> n
 * n + x = size
 *
 */
int rightrot(int x, int n)
{
	int size = sizeof(x) * 8;
	unsigned z = (unsigned)x;
	z = (z >> n) | ((z << (size - n)) & ~0);
	return (int)z;
}

int main()
{
	int x, n, z, r;
	x = 0x70f0f0f1; /* 0111 0000 1111 0000 1111 0000 1111 0001 */
	n = 4;
	z = 0x170f0f0f; /* 0001 0111 0000 1111 0000 1111 0000 1111 */
	r = rightrot(x, n);
	printf("x=%d(0x%08x), z=%d(0x%08x), r=%d(0x%08x)\n", x, x, z, z, r, r);
	x = 0xf0f0f0f1; /* 1111 0000 1111 0000 1111 0000 1111 0001 */
	z = 0x1f0f0f0f; /* 0001 1111 0000 1111 0000 1111 0000 1111 */
	r = rightrot(x, n);
	printf("x=%d(0x%08x), z=%d(0x%08x), r=%d(0x%08x)\n", x, x, z, z, r, r);
	return 0;
}
