/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 07:06:27 PM CST
 * Modified : Sat 04 Aug 2012 09:36:31 PM CST
 */

/*
 * Write a function ``reverse(s)'' that reverses the character string ``s''. Use
 * it to write a program that reverses its input a line at a time.
 */

#include <stdio.h>
#define getline getline2
#define MAXLINE 1024

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

// doesnt reverse '\n'
void reverse(char s[])
{
	int i, j;
	char swap;

	for (j = 0; s[j] != '\0' && s[j] != '\n'; j++) ;

	for (i = 0, j--; i < j; i++, j--) {
		swap = s[i];
		s[i] = s[j];
		s[j] = swap;
	}
}

int main()
{
	char line[MAXLINE];
	int len;
	while ((len = getline(line, MAXLINE - 1)) > 0) {
		// printf("orig: %s", line);
		reverse(line);
		printf("%s", line);
	}
	return 0;
}
