/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 04:44:31 PM CST
 * Modified : Sat 11 Aug 2012 04:45:17 PM CST
 */

/*
 * Define a macro ``swap(t,x,y)'' that interchanges two arguments of type ``t''.
 * (Block structure will help.)
 */

#define swap(t, x, y) do { t z = x; x = y; y = z; } while (0)

#include <stdio.h>
int main()
{
	int a = 1, b = 2;
	char *c = "c", *d = "d";
	printf("a=%d, b=%d, c=%s, d=%s\n", a, b, c, d);
	swap(int, a, b);
	swap(char *, c, d);
	printf("a=%d, b=%d, c=%s, d=%s\n", a, b, c, d);
	return 0;
}
