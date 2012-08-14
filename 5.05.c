/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 11:09:23 PM CST
 * Modified : Sat 11 Aug 2012 11:46:09 PM CST
 */

/*
 * Write versions of the library functions ``strncpy'', ``strncat'', and
 * ``strncmp'', which operate on at most the first ``n'' characters of their
 * argument strings. For example, ``strncpy(s,t,n)'' copies at most ``n''
 * characters of ``t'' to ``s''. Full descriptions are in Appendix B.
 */

#include <stdio.h>
char *strncpy(char *s, const char *t, size_t n)
{
	char *x = s;
	while (n-- > 0 && (*x++ = *t++))
		;
	*x = 0;
	return s;
}


char *strncat(char *s, const char *t, size_t n)
{
	char *x = s;
	while (*x)
		x++;
	while (n-- > 0 && (*x++ = *t++))
		;
	*x = 0;
	return s;
}

int strncmp(const char *s, const char *t, size_t n)
{
	while (--n > 0 && *s && (*s == *t)) {
		s++, t++;
	}

	return (*s - *t);
}

int main()
{
	char t[20];
	const char *x = "hello c!";
	const char *y = "hello world!!!";
	char *s = (char *)&t;
	strncpy(s, "hello ", 6);
	printf("s=%s\n", s);
	strncat(s, "world!helloworld!", 6);
	printf("s=%s\n", s);
	printf("strcmp(s, \"%s\", 5)=%d\n", x, strncmp(s, x, 5));
	printf("strcmp(s, \"%s\", 6)=%d\n", x, strncmp(s, x, 6));
	printf("strcmp(s, \"%s\", 7)=%d\n", x, strncmp(s, x, 7));
	printf("strcmp(s, \"%s\", 13)=%d\n", y, strncmp(s, y, 13));
	return 0;
}
