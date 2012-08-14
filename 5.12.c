/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 11:16:28 AM CST
 * Modified : Mon 13 Aug 2012 10:59:56 PM CST
 */

/*
 * Extend ``entab'' and ``detab'' to accept the shorthand
 * 	``entab -m +n''
 * to mean tab stops every *n* columns, starting at column *m*. Choose
 * convenient (for the user) default behavior.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAB 4

// define PREFERENCE to ' ' or '\t' when a tab or a single blank is equal
#define PREFERENCE ' '

static int entab(int sop, int tab, char preference)
{
	int pos = 0, space = 0;
	int c, extra = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			space++;
		} else {
			// (pos - extra) is the actual position
			while (pos - extra < sop && space > 0) {
				putchar(' ');
				pos++;
				space--;
			}
			while (space > 0) {
				int suffice = (tab - (pos % tab));
				if (suffice == 1) {
					space--;
					putchar(' ');
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

			pos += space;
			while (space > 0) {
				space--;
				putchar(' ');
			}

			putchar(c);
			if (c == '\t') {
				pos += tab - (pos % tab);
				extra += tab - (pos % tab) - 1;
			} else if (c == '\n') {
				pos = 0;
				extra = 0;
			} else {
				pos++;
			}
		}
	}
	return 0;
}

static int detab(int sop, int tab)
{
	int pos = 0;
	int extra = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			pos = 0;
			extra = 0;
			putchar(c);
		} else if (c == '\t' && (pos - extra) >= sop) {
			c = tab - (pos % tab);
			pos += c;
			while (c--) {
				putchar(' ');
			}
		} else {
			putchar(c);
			if (c == '\t') {
				pos += tab - (pos % tab);
				extra += tab - (pos % tab) - 1;
			} else {
				pos++;	/*	space	*/
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int tab = TAB, pos = 0;
	char preference = PREFERENCE;
	char *ch, *function = *argv;

	ch = *argv;
	while (*ch) {
		if (*ch++ == '/') {
			function = ch;
		}
	}
	while (*++argv) {
		ch = *argv;
		if (*ch == '+') {
			tab = atoi(++ch);
			continue;
		} else if (*ch++ != '-') {
			continue;
		}

		if (isdigit(*ch)) { /* -[0-9]* */
			pos = atoi(ch);
		} else if (*ch == 't') { /* -t[0-9] */
			tab = atoi(++ch);
		} else if (*ch == 'p') { /* -pX */
			if (*++ch != '\\') {
				preference = *ch;
			} else if (*++ch == 't') {
				preference = '\t';
			}
		}
	}

	if (strcmp(function, "entab") == 0) {
		entab(pos, tab, preference);
	} else if (strcmp(function, "detab") == 0) {
		detab(pos, tab);
	}
	return 0;
}
