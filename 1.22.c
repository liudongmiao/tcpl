/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 04 Aug 2012 01:09:05 PM CST
 * Modified : Sat 04 Aug 2012 06:56:28 PM CST
 */

/*
 * Write a program to ``fold'' long input lines into two or more shorter lines
 * after the last non-blank character that occurs before the *n*-th column of
 * input. Make sure your program does something intelligent with very long
 * lines, and if there are no blanks or tabs before the specified column.
 */

#include <stdio.h>
#define N 80

#define isspace(x) (x == ' ' || x == '\t' || x == '\n' || x == '\f' || x == '\r' || x == '\v')

int length;
int space;
char word[N];

static void append(int c)
{
	// ltrim the word
	if (isspace(c)) {
		space++;
	}
	word[length] = c;
	length++;
	word[length] = '\0';
}

static void init()
{
	length = 0;
	space = 0;
	word[0] = '\0';
}

int main()
{
	int pos = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			printf("%s%c", word, c);
			init();
			pos = 0;
		} else if (isspace(c)) {
			if (pos + length > N) {
				printf("\n%s", word + space);
				pos = length;
			} else {
				printf("%s", word);
				pos += length;
			}
			init();
			append(c);
		} else {
			append(c);
		}
	}
	return 0;
}
