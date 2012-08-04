/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 02:02:27 PM CST
 * Modified : Sat 04 Aug 2012 09:24:48 PM CST
 */

/*
 * Write a program to count blanks, tabs, and newlines.
 */
#include <stdio.h>

int main()
{
	int c;
	int blank = 0, tab = 0, newline = 0;
	while ((c = getchar()) != EOF) {
		switch (c) {
			case ' ':
				blank++;
				break;
			case '\t':
				tab++;
				break;
			case '\n':
				newline++;
				break;
		}
	}

	printf("blank=%d\n", blank);
	printf("tab=%d\n", tab);
	printf("newline=%d\n", newline);
	return 0;
}
