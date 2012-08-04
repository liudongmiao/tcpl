/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 01:29:45 PM CST
 * Modified : Sat 04 Aug 2012 09:17:58 PM CST
 */

/*
 * Write a program to check a C program for rudimentary syntax errors like
 * unmatched parentheses, brackets and braces. Don't forget about quotes, both
 * single and double, escape sequences, and comments. (This program is hard if
 * you do it in full generality.)
 */

#include <stdio.h>
#include <stdlib.h>

static int pos = 0, line = 1;
static int getchar2() {
	int c = getchar();
	if (c == '\n') {
		line++;
		pos = 0;
	} else {
		pos++;
	}
	return c;
}

#define getchar getchar2

static int stack[128];
int last = 0;

#define check_equal(c, d, e) \
	if (c !=  d) { \
		printf("unparent %c, line %d, pos %d\n", e, line, pos); \
		printf("%s: %s + %d\n", __FUNCTION__, __FILE__, __LINE__); \
		exit(-1); \
	}

#define check_unequal(c, d, e) \
	if (c ==  d) { \
		printf("unparent %c, line %d, pos %d\n", e, line, pos); \
		printf("%s: %s + %d\n", __FUNCTION__, __FILE__, __LINE__); \
		exit(-1); \
	}


/*
\a
\b	backspace
\e	escape	\e[35mpurple\e[0m
\f	form
\n	newline
\r	return
\t	tabe
\u	\u4e00
\v	vertical table
\x	\xXX
*/
int check_slash()
{
	int next;
	next = getchar();
	check_unequal(next, EOF, '\\');

	if (next == 'a' || next == 'b' || next == 'e' || next == 'f' || next == 'n' || next == 'r' || next == 't' || next == 'v') {
		return 0;
	}

	if (next == 'u') {
		printf("\\u is not supported\n");
		return -1;
	}

	if (next == 'x') {
		printf("\\x is not supported\n");
		return -1;
	}

	return 0;
}

// 'X'
int check_single()
{
	int next;

	next = getchar();
	check_unequal(next, EOF, '\'');

	if (next == '\\') {
		check_slash();
	}

	next = getchar();
	check_unequal(next, EOF, '\'');

	check_equal(next, '\'', '\'');
	return 0;
}

int main()
{
	int curr, next = 0;

	while ((curr = getchar()) != EOF && next != EOF) {
		// /?
		if (curr == '/') {
			next = getchar();
			check_unequal(next, EOF, '/');
			// //
			if (next == '/') {
				while ((curr = getchar()) != EOF) {
					if (curr == '\\') {
						check_slash();
					} else if (curr == '\n') {
						break;
					}
				}
			// /*
			} else if (next == '*') {
				while ((curr = getchar()) != EOF) {
					if (curr == '*') {
						next = getchar();
						if (next == '/') {
							break;
						}
					}
				}
				check_unequal(next, EOF, '*');
			// /X
			} else {
				printf("invalid %c%c, 0x%x%x\n", curr, next, curr, next);
				break;
			}
		} else if (curr == '"') {
			while ((curr = getchar()) != EOF) {
				if (curr == '\\') {
					check_slash();
				} else if (curr == '"') {
					break;
				}
			}
			check_unequal(next, EOF, '"');
			check_equal(curr, '"', '"');
		} else if (curr == '\'') {
			check_single();
		} else if (curr == '\\') {
			check_slash();
		} else if (curr == '[' || curr == '{' || curr == '(') {
			last++;
			stack[last] = curr;
		} else if (curr == ']' || curr == '}' || curr == ')') {
			if (last == 0) {
				printf("invalid %c on line %d: %d\n", curr, line, pos);
			}

			if (stack[last] == '[') {
				check_equal(curr, ']', ']');
			}

			if (stack[last] == '{') {
				check_equal(curr, '}', '}');
			}

			if (stack[last] == '(') {
				check_equal(curr, ')', ')');
			}
			last--;
		}
	}

	while (last) {
		printf("unparent %c\n", stack[last]);
		last--;
	}

	return /* comment */ 0;
}
