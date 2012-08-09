/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 03:01:08 PM CST
 * Modified : Thu 09 Aug 2012 09:46:41 AM CST
 */

/*
 * Rewrite the function ``lower'', which converts upper case letters to lower
 * case, with a conditional expression instead of ``if-else''.
 */

#include <stdio.h>

#ifndef ORIGINAL
/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}

#else
int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
	// return (c >= 'A' && c <= 'Z') ? c | 0x20 : c;
}
#endif

int main()
{
	int upper = 'B';
	printf("lower('B')=%c\n", lower(upper));
	return 0;
}
