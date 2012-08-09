/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 01:31:04 PM CST
 * Modified : Thu 09 Aug 2012 02:09:38 PM CST
 */

/*
 * In a two's complement number representation, our version ``itoa'' does not
 * handle the largest negative number, that is, the value of ``n'' equal to
 * -(2**(wordsize-1)). Explain why not. Modify it to print that value correctly,
 *  regardless of the machine on which it runs.
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
void itoa(int n, char s[])
{
	int i, sign;
	unsigned m;
	if ((sign = n) < 0)
		m = -n;
	else
		m = n;
	i = 0;
	do {
		s[i++] = m % 10 + '0';
	} while ((m /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
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
	itoa(m, s);
	printf("s=%s\n", s);
	return 0;
}

