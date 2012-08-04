/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 03:00:23 PM CST
 * Modified : Sat 04 Aug 2012 09:30:46 PM CST
 */

/*
 * Write a program to print a histogram of the frequencies of different
 * characters in its input.
 */

#include <stdio.h>
#include <ctype.h>

#define HEIGHT 20
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static void print(int level)
{
	if (isprint(level)) {
		printf("   %c ", level);
	} else if (level == '\t') {
		printf("  \\t ");
	} else if (level == '\n') {
		printf("  \\n ");
	} else {
		printf("  %02x ", level);
	}
}

static void draw(int *levels, int size)
{
	int length = 0, row = 0;
	int span, level, height;

	for (level = 0; level < size; ++level) {
		if (length < levels[level]) {
			length = levels[level];
		}
	}

	span = length / HEIGHT;
	if (length % HEIGHT) {
		++span;
	}

	row = length / span;
	if (length % span) {
		++row;
	}

	/*
	   0123401234
	   ---- ----
	   |  | |  |
	   |  | |  |
	   |  | |  |
	   |  | |  |
	  -----------
	    04   08
	   */
	for (row+=2; row >= -1; --row)
	{
		for (level = 0; level < size; ++level) {
			height = levels[level] / span;
			if (levels[level] % span) {
				++height;
			}

			if (height == 0) {
				continue;
			}

			if (row == -1) {
				print(level);
			} else if (row == 0) {
				printf("-----");
			} else if (row - height == 2) {
				printf("%5d", levels[level]);
			} else if (row - height == 1) {
				printf(" ____");
			} else if (row <= height) {
				printf(" |xx|");
			} else {
				printf("     ");
			}
		}
		if (row == 0) {
			printf("-");
		}
		printf("\n");
	}
}

int main()
{
	int c, n = 0;
	int levels[0xff] = {0};

	while ((c = getchar()) != EOF) {
		++n;
		++levels[c];
	}

	for (c = 0; c < ARRAY_SIZE(levels); ++c) {
		levels[c] = levels[c] * 100 / n;
	}

	draw(levels, ARRAY_SIZE(levels));
	return 0;
}
