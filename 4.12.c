/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 10 Aug 2012 11:34:22 PM CST
 * Modified : Sat 11 Aug 2012 04:15:02 PM CST
 */

/*
 * Adapt the ideas of ``printd'' to write a recursive version of ``itoa''; that
 * is, convert an integer into a string by calling a recursive routine.
 */

#ifdef NON_STATIC
void itoa(int n, char s[])
{
	int j = 0;
	unsigned m;

	m = (n > 0) ? n : -n;
	if (m / 10 > 0) {
		itoa(n / 10, s);
		while (s[j] != '\0')
			j++;
		s[j++] = "0123456789"[m % 10];
		s[j] = '\0';
	} else if (n < 0) {
		s[j++] = '-';
		s[j++] = "0123456789"[m % 10];
		s[j] = '\0';
	} else {
		s[j++] = "0123456789"[m % 10];
		s[j] = '\0';
	}
}
#else
void itoa(int n, char s[])
{
	static int j = 0;
	static int sign = 0;
	unsigned m;

	if (sign == 0) {
		j = 0;
		sign = (n < 0) ? -1 : 1;
	}

	m = (n > 0) ? n : -n;
	if (m / 10 > 0) {
		itoa(n / 10, s);
	}

	if (sign < 0) {
		s[j++] = '-';
	}

	if (sign != 0) {
		sign = 0;
	}

	s[j++] = "0123456789"[m % 10];
	s[j] = '\0';
}
#endif

#include <stdio.h>
int main()
{
	char s[20];
	itoa(-1234567890, s);
	printf("s=%s\n", s);
	itoa(1234567890, s);
	printf("s=%s\n", s);
	itoa(-1234567890, s);
	printf("s=%s\n", s);
	itoa(1234567890, s);
	printf("s=%s\n", s);
	return 0;
}
