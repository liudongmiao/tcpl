/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 10 Aug 2012 10:38:46 AM CST
 * Modified : Fri 10 Aug 2012 11:03:52 AM CST
 */

/*
 * Our ``getch'' and ``ungetch'' do not handle a pushed-back ``EOF'' correctly.
 * Decide what their properties ought to be if an ``EOF'' is pushed back, then
 * implement your design.
 */
/* XXX: the original should handle EOF correctly. */

#include <stdio.h>
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
	int c;
	while ((c = getch()) != EOF) {
		printf("%c", c);
	}
	printf("push %s%c back: %d\n", (c == EOF) ? "EOF" : "", (c == EOF) ? 0 : c,  c);
	ungetch(c);
	c = getch();
	printf("get EOF: %d\n", c);
	return 0;
}
