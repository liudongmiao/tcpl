/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 04:23:24 PM CST
 * Modified : Sat 11 Aug 2012 04:31:23 PM CST
 */

/*
 * Write a recursive version of the function ``reverse(s)'', which reverses the
 * string ``s'' in place.
 */

void reverse(char s[])
{
	static int i = 0, j = 0;

	if (j == 0) {
		while (s[j] != '\0')
			j++;
		j--;
	}

	if (i < j) {
		char swap;
		swap = s[i];
		s[i++] = s[j];
		s[j--] = swap;
		reverse(s);
	} else {
		i = j = 0;
	}
}

#include <stdio.h>
int main()
{
	char s1[] = "madoldman";
	char s2[] = "thom";
	char s3[] = "123";
	reverse(s1);
	reverse(s2);
	reverse(s3);
	printf("s1=%s, s2=%s, s3=%s\n", s1, s2, s3);
	return 0;
}
