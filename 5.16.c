/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Mon 13 Aug 2012 08:58:50 AM CST
 * Modified : Tue 14 Aug 2012 12:04:40 AM CST
 */

/*
 * Add the ``-d'' (dictionary order) option, which makes comparisons only on
 * letters, numbers and blanks. Make sure it works in conjunction with ``-f''.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
void writelines(char *lineptr[], int nlines, int reverse);
void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int dictcmp(const char *s1, const char *s2);
int ignorecase = 0;

/* sort input lines */
int main(int argc, char **argv)
{
	int nlines;			/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */

#ifndef ORIGINAL
	int reverse = 0;
	int dictionary = 0;
	char lineptr2[MAXLINES][MAXLEN];
	nlines = MAXLINES;
	while (nlines-- > 0) {
		lineptr[nlines] = lineptr2[nlines];
	}
	while (*++argv) {
		if (strcmp(*argv, "-r") == 0) {
			reverse = 1;
		} else if (strcmp(*argv, "-n") == 0) {
			numeric = 1;
		} else if (strcmp(*argv, "-f") == 0) {
			ignorecase = 1;
		} else if (strcmp(*argv, "-d") == 0) {
			dictionary = 1;
		}
	}
#else
	if (argc > 1 && strcmp(argv[1], "-n") == 0) {
		numeric = 1;
	}
#endif

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **)lineptr, 0, nlines - 1,
				(int (*)(void *, void*))(numeric ? numcmp :
					(dictionary ? dictcmp : (ignorecase ? strcasecmp : strcmp))));
		writelines(lineptr, nlines, reverse);
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
void writelines(char *lineptr[], int nlines, int reverse)
{
	if (reverse) {
		lineptr += (nlines - 1);
		while (nlines-- > 0)
			printf("%s\n", *lineptr--);

	} else {
		while (nlines-- > 0)
			printf("%s\n", *lineptr++);
	}
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
		int (*comp)(void *, void*))
{
	int i, last;
	void swap(void *v[], int i, int j);

	if (left >= right)	/* do nothing if array contains */
		return;			/* fewer than two elements */
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1, comp);
	qsort(v, last + 1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* nummcp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* dictcmp */
int dictcmp(const char *s1, const char *s2)
{
	char c1, c2;
	while (1) {
		while (*s1 && !isalnum(*s1) && !isblank(*s1))
			s1++;
		while (*s2 && !isalnum(*s2) && !isblank(*s2))
			s2++;

		if (!*s1 || !*s2) {
			break;
		}

		if (ignorecase) {
			c1 = toupper(*s1);
			c2 = toupper(*s2);
		} else {
			c1 = *s1;
			c2 = *s2;
		}

		if (c1 < c2)
			return -1;
		else if (c1 > c2)
			return 1;
		s1++, s2++;
	}

	if (*s1 < *s2)
		return -1;
	else if (*s1 > *s2)
		return 1;
	else
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

char *alloc(int n)
{
	return (char *)malloc(n);
}

void afree(char *p)
{
	free(p);
}
