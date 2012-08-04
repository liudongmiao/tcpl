/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 08:18:09 PM CST
 * Modified : Sat 04 Aug 2012 06:47:34 PM CST
 */

/*
 * Write a program ``detab'' that replaces tabs in the input with the proper
 * number of blanks to space to the next tab stop. Assume a fixed set of tab
 * stops, say every *n* columns. Should *n* be a variable or a symbolic
 * parameter?
 */

#include <stdio.h>
#define TAB 5

int main()
{
	int pos = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			pos = 0;
			putchar(c);
		} else if (c == '\t') {
			/*	place a blank first */
			/*	or use do ... while */
			/*
			c = TAB - (pos % TAB);
			while (c) {
				putchar(' ');
				c--;
			}
			pos += c;
			*/
			putchar(' ');
			pos++;
			while ((pos % TAB) != 0) {
				putchar(' ');
				pos++;
			}
		} else {
			putchar(c);
			pos++;	/*	space	*/
		}
	}
	return 0;
}
