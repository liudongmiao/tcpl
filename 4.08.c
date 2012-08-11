/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 10 Aug 2012 10:38:46 AM CST
 * Modified : Fri 10 Aug 2012 10:53:38 AM CST
 */

/*
 * Suppose that there will never be more than one character of pushback. Modify
 * ``getch'' and ``ungetch'' accordingly.
 */

#include <stdio.h>
int buf = EOF;
int getch(void)
{
	int tmp;
	tmp = buf;
	buf = EOF;
	return (tmp != EOF) ? tmp : getchar();
}

void ungetch(int c)		/* push character back on input */
{
	if (buf != EOF) {
		printf("ungetch: too many characters\n");
	} else {
		buf = c;
	}
}

int main()
{
	int c;
	c = getch();
	printf("c=%c\n", c);
	ungetch(c);
	c = getch();
	printf("c=%c\n", c);
	c = getch();
	printf("c=%c\n", c);
	return 0;
}
