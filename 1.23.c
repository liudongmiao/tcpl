/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 01:29:45 PM CST
 * Modified : Sat 04 Aug 2012 09:23:44 PM CST
 */

/*
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't
 * nest.
 */

#include <stdio.h>

/* ... */
// ....
#define A "/*..*/\".\\"/*.*/"ABC" "DEF"
#define B "ABC\\"A
// newline \
#define C "shouldnt"

int main()
{
	int curr, next = 0;

	while ((curr = getchar()) != EOF && next != EOF) {
		// comment starts with /?
		if (curr == '/') {
			next = getchar();
			if (next == EOF) {
				break;
			}
			// //
			if (next == '/') {
				while ((curr = getchar()) != EOF) {
					if (curr == '\\') {
						next = getchar();
						if (next == EOF) {
							break;
						}
					} else if (curr == '\n') {
						putchar(curr);
						break;
					}
				}
			// /*
			} else if (next == '*') {
				while ((curr = getchar()) != EOF) {
					if (curr == '*') {
						next = getchar();
						if (next == EOF || next == '/') {
							break;
						}
					}
				}
			// /X
			} else {
				// shouldnt happen
			}
		// /? in " is not comment
		} else if (curr == '"') {
			putchar(curr);
			while ((curr = getchar()) != EOF) {
				putchar(curr);
				if (curr == '\\') {
					next = getchar();
					if (next == EOF) {
						break;
					}
					putchar(next);
				} else if (curr == '"') {
					break;
				}
			}
		// " in ' is not comment
		} else if (curr == '\'') {
			putchar(curr);
			next = getchar();
			if (next == EOF) {
				break;
			}
			putchar(next);
		} else {
			putchar(curr);
		}
	}
	return /* comment */ 0;
}
