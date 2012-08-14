/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Mon 13 Aug 2012 05:13:27 PM CST
 * Modified : Tue 14 Aug 2012 08:48:49 AM CST
 */

/*
 * Write the program ``tail'', which prints the last *n* lines of its input. By
 * default, *n* is set to 10, let us say, but it can be changed by an optional
 * argument so that
 * 		``tail -n''
 * prints the last *n* lines. The program should behave rationally no matter how
 * unreasonable the input or the value of *n*. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program of Section 5.6, not in a two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define getline getline2
int getline(char *, int);

void tail(int n)
{
	int i, len;
	char buffer[BUFSIZ], **line, **lines;

	lines = malloc(n * sizeof(lines));
	line = lines;
	for (i = 0; i < n; i++) {
		*line = NULL;
		line++;
	}
	while ((len = getline(buffer, BUFSIZ)) > 0) {
		if (line - lines >= n) {
			line -= n;
		}
		if (!*line) {
			*line = malloc(len);
		} else if (strlen(*line) < len) {
			*line = realloc(*line, len);
		}

		buffer[len - 1] = '\0';
		strcpy(*line, buffer);
		line++;
	}

	for (i = 0; i < n; i++) {
		if (line - lines >= n) {
			line -= n;
		}
		if (*line) {
			printf("%s\n", *line);
			free(*line);
		}
		line++;
	}

	free(lines);
}

int main(int argc, char **argv)
{
	int count = 10;
	char *p;
	while (*++argv) {
		p = *argv;
		if (*p++ == '-' && isdigit(*p)) {
			count = atoi(p);
		}
	}

	tail(count);
	return 0;
}

int getline(char *s, int lim)
{
	int c;
	char *x = s;
	while (lim-- > 0 && (c = getchar()) != EOF && c != '\n') {
		*x++ = c;
	}
	if (c == '\n') {
		*x++ = c;
	}
	*x = '\0';

	return (x - s);
}
