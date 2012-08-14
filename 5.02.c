/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 06:00:26 PM CST
 * Modified : Sat 11 Aug 2012 06:00:37 PM CST
 */

/*
 * Write ``getfloat'', the floating-point analog of ``getint''. What type does
 * ``getfloat'' return as its function value?
 */

#include <stdio.h>
#include <ctype.h>
int getch(void);
void ungetch(int);

int getfloat(double *pn)
{
	int c, sign;
	double power;
	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);
		return 0;
	}

	/* sign */
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c) && c != '.') {
			ungetch(c);
			ungetch((sign == -1) ? '-' : '+');
			return 0;
		}
	}

	// integer
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');

	// point
	if (c == '.') {
		c = getch();
	}

	// float
	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}

	*pn *= sign;
	*pn /= power;

	// e
	if (c == 'e' || c == 'E') {
		c = getch();
		if (isdigit(c) || c == '+' || c == '-') {
			int e;
			sign = (c == '-') ? -1 : 1;
			if (!isdigit(c)) {
				c = getch();
			}

			for (e = 0; isdigit(c); c = getch()) {
				e = 10 * e + (c - '0');
			}

			while (e-- > 0) {
				if (sign > 0) {
					*pn *= 10.0;
				} else {
					*pn /= 10.0;
				}
			}
		}
	}

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

int main()
{
	double f;
	getfloat(&f);
	printf("f=%f\n", f);
	return 0;
}
