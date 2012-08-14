/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 05:27:00 PM CST
 * Modified : Sat 11 Aug 2012 05:37:08 PM CST
 */

/*
 * As written, ``getint'' treats a ``+'' or ``-'' not followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the
 * input.
 */


#include <stdio.h>
#include <ctype.h>
int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
#ifndef ORIGINAL
	{
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			ungetch((sign == -1) ? '-' : '+');
			return 0;
		}
	}
#else
		c = getch();
#endif
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)		/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
