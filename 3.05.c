/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 01:31:04 PM CST
 * Modified : Thu 09 Aug 2012 01:57:58 PM CST
 */

/*
 * Write the function ``itob(n,s,b)'' that converts the integer ``n'' into a
 * base ``b'' character representation in the string ``s''. In particular,
 * ``itob(n,s,16)'' formats ``s'' as a hexadecimal integer in ``s''.
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

#define STRING "0123456789abcdefghijklmnopqrstuvwxyz"
void itob(int n, char s[], int b)
{
	int i, sign;
	unsigned m;
	if ((sign = n) < 0)
		m = -n;
	else
		m = n;
	i = 0;
	do {
		s[i++] = STRING[m % b];
	} while ((m /= b) > 0);
	if (b == 16) {
		s[i++] = 'x';
		s[i++] = '0';
	} else if (b == 8) {
		s[i++] = '0';
	} else if (b == 2) {
		s[i++] = 'b';
		s[i++] = '0';
	}
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

#include <stdio.h>
#define MIN(x) (-(x >> 1) - 1)
int main()
{
	int m = MIN((unsigned int)~0);
	char s[32];
	printf("m=%d(0x%0x)\n", m, m);
	itob(m, s, 16);
	printf("s=%s\n", s);
	m = 0xffff;
	itob(m, s, 10);
	printf("s=%s\n", s);
	itob(m, s, 8);
	printf("s=%s\n", s);
	itob(m, s, 2);
	printf("s=%s\n", s);
	return 0;
}
