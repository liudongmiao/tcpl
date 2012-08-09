/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 01:18:32 PM CST
 * Modified : Thu 09 Aug 2012 03:09:22 PM CST
 */

/*
 * Write a function ``expand(s1, s2)'' that expands shorthand notations like
 * ``a-z'' in the string ``s1'' into the equivalent complete list ``abc...xyz''
 * in ``s2''. Allow for letters of either case and digits, and be prepared to
 * handle cases like ``a-b-c'' and ``a-z0-9'' and ``-a-z''. Arrange that a
 * leading or trailing ``-'' is taken literally.
 */

#include <stdio.h>
#define FIRST 0x20
#define LAST 0x7e
void expand(const char s1[], char s2[])
{
	int i, j, k;
	int min, max;
	for (i = 0, j = 0; s1[i] != '\0'; i++) {
		if (s1[i] == '-') {
			if (i != 0) {
				min = s1[i - 1] + 1;
			} else {
				min = FIRST;
			}

			if (s1[i + 1] != '\0') {
				max = s1[i + 1] - 1;
			} else {
				max = LAST;
			}

			for (k = min; k <= max; k++) {
				s2[j++] = k;
			}
		} else {
			s2[j++] = s1[i];
		}
	}
}

int main()
{
	char s1[] = "-a-b-ca-z0-9A-Za-z-";
	char s2[1024] = {0};
	expand(s1, s2);
	printf("s1=%s\n", s1);
	printf("s2=%s\n", s2);
	return 0;
}
