/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 11:16:28 AM CST
 * Modified : Mon 13 Aug 2012 03:42:53 PM CST
 */

/*
 * Modify the program ``entab'' and ``detab'' (written as exercises in Chapter
 * 1) to accept a list of tab stops as arguments, Use the default tab settings
 * if there are no arguments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAB 4

// define PREFERENCE to ' ' or '\t' when a tab or a single blank is equal
#define PREFERENCE ' '

static int entab(int tab, char preference)
{
	int pos = 0, space = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			space++;
		} else {

			while (space > 0) {
				int suffice = (tab - (pos % tab));
				if (suffice == 1) {
					space--;
					putchar(preference);
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

static int detab(int tab)
{
	int pos = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			pos = 0;
			putchar(c);
		} else if (c == '\t') {
			c = tab - (pos % tab);
			pos += c;
			while (c--) {
				putchar(' ');
			}
		} else {
			putchar(c);
			pos++;	/*	space	*/
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int tab = TAB;
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
		if (*ch++ != '-') {
			continue;
		}
		if (*ch == 't') {
			tab = atoi(++ch);
		} else if (*ch == 'p') {
			if (*++ch != '\\') {
				preference = *ch;
			} else if (*++ch == 't') {
				preference = '\t';
			}
		}
	}

	if (strcmp(function, "entab") == 0) {
		entab(tab, preference);
	} else if (strcmp(function, "detab") == 0) {
		detab(tab);
	}
	return 0;
}
