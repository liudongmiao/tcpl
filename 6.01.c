/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Tue 14 Aug 2012 04:07:28 PM CST
 * Modified : Wed 15 Aug 2012 03:24:27 PM CST
 */

/* Our version of ``getword'' does not properly handle underscores, string
 * constants, comments, or preprocessor control lines. Write a better version.
 */

struct key {
	char *word;
	int count;
} keytab[] = {
	{"asm", 0},
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	{"const", 0},
	{"continue", 0},
	{"default", 0},
	{"do", 0},
	{"double", 0},
	{"else", 0},
	{"enum", 0},
	{"extern", 0},
	{"float", 0},
	{"for", 0},
	{"goto", 0},
	{"if", 0},
	{"int", 0},
	{"long", 0},
	{"register", 0},
	{"return", 0},
	{"short", 0},
	{"signed", 0},
	{"sizeof", 0},
	{"static", 0},
	{"struct", 0},
	{"switch", 0},
	{"typedef", 0},
	{"union", 0},
	{"unsigned", 0},
	{"unsigned", 0},
	{"void", 0},
	{"volatile", 0},
	{"while", 0}
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
int getword(char *, int);
int binsearch(char *, struct key *, int);
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

/* count C keywords */
int main()
{
	int n;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
					keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low  = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

#ifdef ORIGINAL
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
#else
	while (isspace(c = getch()))
		;
	if (c == '/') {
		if ((c = getch()) == EOF) {
			return EOF;
		} else if (c == '/') {
			while ((c = getch()) != EOF) {
				if (c == '\\') {
					if ((c = getch()) == EOF) {
						return EOF;
					}
				} else if (c == '\n') {
					break;
				}
			}
		} else if (c == '*') {
			while ((c = getchar()) != EOF) {
				if (c == '*') {
					if ((c = getch()) == EOF) {
						return EOF;
					} else if (c == '/') {
						break;
					}
				}
			}
		}
		return c;
	} else if (c == '"') {
		while ((c = getch()) != EOF) {
			if (c == '\\') {
				if ((c = getch()) == EOF) {
					return EOF;
				}
			} else if (c == '"') {
				break;
			}
		}
		return c;
	} else if (c == '\'') {
		if ((c = getchar()) == EOF) {
			return EOF;
		} else if (c == '\\') {
			if ((c = getchar()) == EOF) {
				return EOF;
			}
		}
		c = getchar();
		return c;
	} else if (isalpha(c) || (c == '_')) {
		*w++ = c;
		while (w - word < lim && (*w = getch()) != EOF && (isalnum(*w) || *w == '_'))
			w++;
	} else if (c == EOF) {
		return EOF;
	}
#endif
	*w = '\0';
	return word[0];
}

int buf = EOF;
int getch(void)
{
	int tmp = buf;
	buf = EOF;
	return (tmp != EOF) ? tmp : getchar();
}

void ungetch(int c)
{
	if (buf != EOF) {
		printf("ungetch: too many characters\n");
	} else {
		buf = c;
	}
}
