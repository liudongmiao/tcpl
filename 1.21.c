/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 11:16:28 AM CST
 * Modified : Sat 04 Aug 2012 12:53:55 PM CST
 */

/*
 * Write a program ``entab'' that replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. Use the same tab stops
 * as for ``detab''. When either a tab or a single blank would suffice to reach
 * a tab stop, which should be given preference?
 */

#include <stdio.h>
#define TAB 5

// define PREFERENCE to ' ' or '\t' when a tab or a single blank is equal
#define PREFERENCE ' '

int main()
{
	int pos = 0, space = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			space++;
		} else {

			while (space > 0) {
				int suffice = (TAB - (pos % TAB));
				if (suffice == 1) {
					space--;
					putchar(PREFERENCE);
				} else if (space >= suffice) {
					space -= suffice;
					putchar('\t');
				} else {
					while (space > 0) {
						space--;
						putchar(' ');
					}
				}
				pos += suffice;
			}

			putchar(c);
			pos++;
			if (c == '\n') {
				pos = 0;
			}
		}
	}
	return 0;
}
