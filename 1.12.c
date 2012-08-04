/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 02:44:26 PM CST
 * Modified : Sat 04 Aug 2012 09:28:11 PM CST
 */

/*
 * Write a program that prints its input one word per line.
 */

#include <stdio.h>

#define isspace(x) (x == ' ' || x == '\t' || x == '\n' || x == '\f' || x == '\r' || x == '\v')

#define TRUE 1
#define FALSE 0

int main()
{
	int c = 0;
	int inspace = FALSE;

	while ((c = getchar()) != EOF) {
		if (isspace(c)) {
			if (FALSE == inspace) {
				putchar('\n');
			}
			inspace = TRUE;
		} else {
			inspace = FALSE;
			putchar(c);
		}
	}

	return 0;
}
