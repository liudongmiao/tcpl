/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 02:02:27 PM CST
 * Modified : Sat 04 Aug 2012 09:27:04 PM CST
 */

/*
 * Write a program to copy its input to its output, replacing each tab by
 * ``\t'', each backspace by ``\b'', and each backslash by ``\\''. This makes
 * tabs and backspaces visible in an unambiguous way.
 */

#include <stdio.h>

int main()
{
	int c;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case '\t':
				putchar('\\');
				putchar('t');
				break;
			case '\b':
				putchar('\\');
				putchar('b');
				break;
			case '\\':
				putchar('\\');
				putchar('\\');
				break;
			default:
				putchar(c);
				break;
		}
	}

	return 0;
}
