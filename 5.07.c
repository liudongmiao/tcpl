/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Mon 13 Aug 2012 08:58:50 AM CST
 * Modified : Mon 13 Aug 2012 10:46:17 AM CST
 */

/*
 * Rewrite ``readlines'' to store lines in an array supplied by main, rather
 * than calling ``alloc'' to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _STDIO_H
#define getline getline2
#endif

#ifdef _STDLIB_H
#define qsort qsort2
#endif

#define MAXLINES 5000		/* max #lines to be sorted */
#define MAXLEN 1000			/* max length of any input line */
int getline(char *, int);
char *alloc(int);

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
	int nlines;			/* number of input lines read */
#ifndef ORIGINAL
	char lineptr2[MAXLINES][MAXLEN];
	nlines = MAXLINES;
	while (nlines-- > 0) {
		lineptr[nlines] = lineptr2[nlines];
	}
#endif
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
#ifdef ORIGINAL
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';	/* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
#else
	int len, nlines;

	nlines = 0;
	while (nlines < maxlines && (len = getline(lineptr[nlines], MAXLEN)) > 0) {
		lineptr[nlines++][len - 1] = '\0';
	}

	return nlines;
#endif
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;			/* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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

char *alloc(int n)
{
	return (char *)malloc(n);
}

void afree(char *p)
{
	free(p);
}
