/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 10:14:34 PM CST
 * Modified : Sat 11 Aug 2012 10:37:32 PM CST
 */

/*
 * Write the function ``strend(s,t)'', which returns 1 if the string ``t''
 * occurs at the end of the string ``s'', and zero otherwise.
 */

int strend(const char *s, const char *t)
{
	const char *x = s, *y = t;

	while (*x)
		x++;
	while (*y)
		y++;

	if (y - t > x - s) {
		return 0;
	}

	while (*x-- == *y-- && y - t > 0)
		;

	return !(t - y);
}

#include <stdio.h>
int main()
{
	const char *s = "hello world";
	const char *t = "world";
	const char *x = "hello world";
	printf("%d\n", strend(s, t));
	printf("%d\n", strend(t, s));
	printf("%d\n", strend(s, x));
	return 0;
}
