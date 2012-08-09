/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 01:31:04 PM CST
 * Modified : Thu 09 Aug 2012 02:03:19 PM CST
 */

/*
 * Write a version of ``itoa'' that accepts three arguments instead of two. The
 * third argument is a minimum field width; the converted number must be padded
 * with blanks on the left if necessary to make it wide enough.
 */

// copy it from 1.19
void reverse(char s[])
{
	int i, j;
	char swap;

	for (j = 0; s[j] != '\0' && s[j] != '\n'; j++) ;

	for (i = 0, j--; i < j; i++, j--) {
		swap = s[i];
		s[i] = s[j];
		s[j] = swap;
	}
}

#ifdef ORIGINAL
/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0)	/* record sign */
		n = -n;			/* make n positive */			/* XXX: overflow here */
	i = 0;
	do {		/* generate digits in reverse order */
		s[i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
#else
void itoa(int n, char s[], int w)
{
	int i, sign;
	unsigned m;
	if ((sign = n) < 0)	{
		m = -n;
	} else {
		m = n;
	}
	i = 0;
	do {
		w--, s[i++] = m % 10 + '0';
	} while ((m /= 10) > 0);
	if (sign < 0) {
		w--, s[i++] = '-';
	}
	while (w > 0) {
		w--, s[i++] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}
#endif

#include <stdio.h>
#define MIN(x) (-(x >> 1) - 1)
int main()
{
	int m = MIN((unsigned int)~0);
	char s[32];
	printf("m=%d(0x%0x)\n", m, m);
	itoa(m, s, 31);
	printf("s=%s\n", s);
	return 0;
}
