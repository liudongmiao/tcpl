/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 09:57:12 PM CST
 * Modified : Sat 04 Aug 2012 10:20:48 PM CST
 */

/*
 * Write a program to determine the ranges of ``char'', ``short'', ``int'', and
 * ``long'' variables, both ``signed'' and ``unsigned'', by printing appropriate
 * values from standard headers and by direct computation. Harder if you compute
 * them: determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>

int main()
{
	unsigned char c = ~0;
	unsigned short s = ~0;
	unsigned int i = ~0;
	unsigned long l = ~0;

	printf("char min: %d, max: %d, unsigned max: %u\n", CHAR_MIN, CHAR_MAX, UCHAR_MAX);
	printf("short min: %d, max: %d, unsigned max: %u\n", SHRT_MIN, SHRT_MAX, USHRT_MAX);
	printf("int min: %d, max: %d, unsigned max: %u\n", INT_MIN, INT_MAX, UINT_MAX);
	printf("long min: %ld, max: %ld, unsigned max: %lu\n", LONG_MIN, LONG_MAX, ULONG_MAX);

#define MIN(x) (-(x >> 1) - 1)
#define MAX(x) (x >> 1)
#define UMAX(x) x
	printf("char min: %d, max: %d, unsigned max: %u\n", MIN(c), MAX(c), UMAX(c));
	printf("short min: %d, max: %d, unsigned max: %u\n", MIN(s), MAX(s), UMAX(s));
	printf("int min: %d, max: %d, unsigned max: %u\n", MIN(i), MAX(i), UMAX(i));
	printf("long min: %ld, max: %ld, unsigned max: %lu\n", MIN(l), MAX(l), UMAX(l));

	return 0;
}
