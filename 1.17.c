/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 06:43:46 PM CST
 * Modified : Sat 04 Aug 2012 09:33:35 PM CST
 */

/*
 * Write a program to print all input lines that are longer than 80 characters.
 */

#include <stdio.h>
#define getline getline2

#define LENGTH 80

int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}


int main()
{
	char line[LENGTH + 1];
	int c, len;
	while ((len = getline(line, LENGTH)) > 0) {
		if (line[len-1] != '\n') {
			printf("%s", line);
			while ((c = getchar()) != EOF && c != '\n') {
				putchar(c);
			}
			if (c != EOF) {
				putchar(c);
			}
		}
	}
	return 0;
}
