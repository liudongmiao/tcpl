/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 02:02:27 PM CST
 * Modified : Sat 04 Aug 2012 09:26:04 PM CST
 */

/*
 * Write a program to copy its input to its output, replacing each string of one
 * or more blanks by a single blank.
 */

#include <stdio.h>

int main()
{
	int c;
	int last = EOF;
	while ((c = getchar()) != EOF) {
		if (c == ' ' && last == c) {
			continue;
		}
		last = c;
		putchar(c);
	}

	return 0;
}
