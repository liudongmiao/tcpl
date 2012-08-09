/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 12:41:17 PM CST
 * Modified : Thu 09 Aug 2012 10:01:54 AM CST
 */

/*
 * Write a function ``htoi(s)'', which converts a string of hexadecimal digits
 * (including an optional ``0x'' or ``0X'') into its equivalent integer value.
 * The allowable digits are ``0'' through ''9'', ``a'' through ``f'', and ``A''
 * through ``F''.
 */

#include <stdio.h>

#define STRING "0123456789aAbBcCdDeEfF"
int htoi(const char s[])
{
	int i, n, j;
	const char h[] = STRING;
	for (i = 0, n = 0; s[i] != '\0'; ++i) {
		for (j = 0; s[i] != h[j] && h[j] != '\0'; ++j) ;
		if (s[i] == h[j]) {
			if (j < 10) {
				n = 16 * n + j;
			} else {
				n = 16 * n + (j - 10) / 2 + 10;
			}
		}
	}
	return n;
}

int main()
{
	printf("htoi[0xFF] = %x\n", htoi("0xFF"));
	printf("htoi[0xab] = %x\n", htoi("0xab"));
	printf("htoi[0x56] = %x\n", htoi("0x56"));
	return 0;
}
