/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 10 Aug 2012 10:38:46 AM CST
 * Modified : Fri 10 Aug 2012 10:42:15 AM CST
 */

/*
 * Write a routine ``ungets(s)'' that will push back an entire string onto the
 * input. Should ``ungets'' know about ``buf'' and ``bufp'', or should it just
 * use ``ungetch''?
 */

#include <stdio.h>
#define MAXOP 100
#define NUMBER '0'

#include <ctype.h>
int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
#ifdef ORIGINAL
	if (!isdigit(c) && c != '.')
		return c; 		/* not a number */
	i = 0;
#else
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	i = 0;
	if (c == '-') {
		c = getch();
		if (!isdigit(c) && c != '.') {
			ungetch(c);
			return '-';
		}
		s[++i] = c;
	}
#endif
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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

void ungets(char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; i++) ;
	for (i--; i >= 0; i--) {
		ungetch(s[i]);
	}
}

int main()
{
	char s[MAXOP];
	getop(s);
	printf("s=%s\n", s);
	ungets(s);
	getop(s);
	printf("s=%s\n", s);
	getop(s);
	printf("s=%s\n", s);
	return 0;
}
