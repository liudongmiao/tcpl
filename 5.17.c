/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Tue 14 Aug 2012 09:12:11 AM CST
 * Modified : Tue 14 Aug 2012 10:42:20 AM CST
 */

/*
 * Add a field-searching capability, so sorting may be done on fields within
 * lines, each field sorted according to an independent set of options. (The
 * index for this book was sorted with ``-df'' for the index category and ``-n''
 * for the page numbers.)
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

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int dictcmp(const char *s1, const char *s2, int igncase);
int fieldcmp(const char *s1, const char *s2);

#define REVERSE 0x1
#define NUMERIC 0x2
#define IGNCASE 0x4
#define DICTION 0x8
#define MAXFIELD 10
int fields[MAXFIELD] = {-1};

/* sort input lines */
int main(int argc, char **argv)
{
	int nlines;			/* number of input lines read */
	int *field = fields;
	char lineptr2[MAXLINES][MAXLEN];
	nlines = MAXLINES;
	while (nlines-- > 0) {
		lineptr[nlines] = lineptr2[nlines];
	}
	while (field - fields < MAXFIELD && *++argv) {
		if (**argv == '-') {
			*field = 0;
			while (*++*argv) {
				switch (**argv) {
					case 'r':
						*field |= REVERSE;
						break;
					case 'n':
						*field |= NUMERIC;
						break;
					case 'f':
						*field |= IGNCASE;
						break;
					case 'd':
						*field |= DICTION;
						break;
				}
			}
			if (*field & NUMERIC) {
				printf("options nd is incompatible, use n\n");
			}
		}
		field++;
		*field = -1;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))fieldcmp);
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
	int len, nlines;

	nlines = 0;
	while (nlines < maxlines && (len = getline(lineptr[nlines], MAXLEN)) > 0) {
		lineptr[nlines++][len - 1] = '\0';
	}

	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
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
int dictcmp(const char *s1, const char *s2, int igncase)
{
	igncase = (igncase) ? 0x20 : 0;
	while (1) {
		while (*s1 && !isalnum(*s1) && !isblank(*s1))
			s1++;
		while (*s2 && !isalnum(*s2) && !isblank(*s2))
			s2++;

		if (!*s1 || !*s2) {
			break;
		}

		if ((*s1 | igncase) < (*s2 | igncase))
			return -1;
		else if ((*s1 | igncase) > (*s2 | igncase))
			return 1;
		s1++, s2++;
	}

	if ((*s1 | igncase) < (*s2 | igncase))
		return -1;
	else if ((*s1 | igncase) > (*s2 | igncase))
		return 1;
	else
		return 0;
}

#define SETFIELD(x) do {\
	while (*x && !isblank(*x)) \
		x++;\
	if (*x != '\0') {\
		*x = '\0';\
		x++;\
	}\
} while (0)
int fieldcmp(const char *s1, const char *s2)
{
	int result = 0;
	int *field = fields;
	char *s1dup, *s2dup;
	char *current1, *next1;
	char *current2, *next2;
	s1dup = strdup(s1), s2dup = strdup(s2);
	current1 = s1dup, current2 = s2dup;
	while (*field != -1 && *current1 && *current2) {
		next1 = current1, next2 = current2;
		SETFIELD(next1);
		SETFIELD(next2);

		if (*field & NUMERIC) {
			result = numcmp(current1, current2);
		} else if (*field & DICTION) {
			result = dictcmp(current1, current2, *field & IGNCASE);
		} else if (*field & IGNCASE) {
			result = strcasecmp(current1, current2);
		} else {
			result = strcmp(current1, current2);
		}

		if (result) {
			result = (*field & REVERSE) ? -result : result;
			break;
		}

		current1 = next1, current2 = next2;
		field++;
	}

	if (!result) {
		result = strcmp(current1, current2);
	}

	free(s1dup), free(s2dup);
	return result;
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
