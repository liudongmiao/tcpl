/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 03:00:23 PM CST
 * Modified : Sat 04 Aug 2012 09:29:47 PM CST
 */

/*
 * Write a program to print a histogram of the lengths of words in its input. It
 * is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 */

#include <stdio.h>

#define HEIGHT 20
#define SPAN 4
#define LENGTH 32
#define isspace(x) (x == ' ' || x == '\t' || x == '\n' || x == '\f' || x == '\r' || x == '\v')
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

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
				printf("  %02d ", (level+1) * SPAN);
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
	int c, length = 0;
	int levels[LENGTH / SPAN + 1] = {0};

	while ((c = getchar()) != EOF) {
		if (isspace(c)) {
			if (length > 0) {
				length = length > LENGTH ? LENGTH : length;
				++levels[length % SPAN ? length / SPAN : length / SPAN - 1];
			}
			length = 0;
		} else {
			++length;
		}
	}

	draw(levels, ARRAY_SIZE(levels));
	return 0;
}
