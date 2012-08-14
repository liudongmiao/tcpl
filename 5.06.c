/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 11:58:06 PM CST
 * Modified : Sun 12 Aug 2012 01:03:28 AM CST
 */

/*
 * Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilities include ``getline''
 * (Chapters 1 and 4), ``atoi'', ``itoa'', and their variants (Chapters 2, 3,
 * and 4), ``reverse'' (Chapter 3), and ``strindex'' and ``getop'' (Chapter 4).
 */

#include <stdio.h>
#include <ctype.h>

#define getline getline2
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

int atoi(char *s)
{
	int n = 0, sign = 1;;
	while (isspace(*s))
		s++;

	if (*s == '-' || *s == '+') {
		sign = (*s++ == '-') ? -1 : 1;
	}

	while (isdigit(*s)) {
		n = 10 * n + (*s++ - '0');
	}

	n *= sign;
	return n;
}

char *itoa(int n, char *s)
{
	unsigned m;

	m = (n > 0) ? n : -n;
	if (m / 10 > 0) {
		s = itoa(n / 10, s);
	} else if (n < 0) {
		*s++ = '-';
	}
	*s++ = "0123456789"[m % 10];
	*s = '\0';

	return s;
}

void reverse(char *s)
{
	char swap;
	char *x = s;

	while (*x) {
		x++;
	}

	x--;
	while (x - s > 0) {
		swap = *s;
		*s++ = *x;
		*x-- = swap;
	}
}

/*
 * Write the function ``strindex(s,t)'' which returns the position of the
 * *rightmost* occurrence of ``t'' in ``s'', or ``-1'' if there is none.
 */

int strindex(const char *s, const char *t)
{
	const char *x = s, *y = t, *z;
	while (*x)
		x++;
	while (*y)
		y++;
	x -= (y - t);
	while (x - s >= 0) {
		z = x;
		y = t;
		while (*y && *z++ == *y++)
			;
		if (*y == 0) {
			return x - s;
		}
		x--;
	}

	return -1;
}

int getch(void);
void ungetch(int c);

/* getop: get next character or numeric operand */
int getop(char *s)
{
	int c;
	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*++s = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	s--;
	if (c == '-') {
		c = getch();
		if (!isdigit(c) && c != '.') {
			ungetch(c);
			return '-';
		}
		*++s = c;
	}
	if (isdigit(c))		/* collect integer part */
		while (isdigit(*++s = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(*++s = c = getch()))
			;
	*s = '\0';
	if (c != EOF)
		ungetch(c);
	return '\0';
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

#define MAX 50
#define NUM1 "12345"
#define NUM2 "-12345"
int main()
{
	char s[32];
	/*
	int i;
	char line[MAX + 1];
	while ((i = getline((char *)&line, MAX)) != 0) {
		if (i < MAX) {
			printf("line=%s", line);
		} else {
			printf("line=%s\n", line);
			break;
		}
	}
	*/
	printf("atoi(%s)=%d\n", NUM1, atoi(NUM1));
	printf("atoi(%s)=%d\n", NUM2, atoi(NUM2));

	itoa(12345, (char *)&s);
	printf("s = %s\n", s);
	itoa(-12345, (char *)&s);
	printf("s = %s\n", s);
	reverse(s);
	printf("s = %s\n", s);
	s[0] = '\0';
	reverse(s);
	printf("s = %s\n", s);
	{
		const char *s = "hello";
		const char *t = "hello";
		int pos = strindex(s, t);
		printf("s=%s, t=%s, pos=%d\n", s, t, pos);
	}
	{
		while (getop((char *)&s) != 'q') {
			if (*s != '\n') {
				printf("s=%s\n", s);
			}
		}
	}
	return 0;
}
