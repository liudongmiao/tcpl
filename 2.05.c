/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 01:30:44 PM CST
 * Modified : Wed 08 Aug 2012 01:33:11 PM CST
 */

/*
 * Write the function ``any(s1, s2)'', which returns the first location in a
 * string ``s1'' where any character from the string ``s2'' occurs, or ``-1'' if
 * ``s1'' contains no characters from ``s2''. (The standard library function
 * ``strpbrk'' does the same job but returns a pointer to the location.)
 */

#include <stdio.h>

int any(const char s1[], const char s2[])
{
	int i, j;
	for (i = 0; s1[i] != '\0'; i++) {
		for (j = 0; s1[i] != s2[j] && s2[j] != '\0'; j++) ;
		if (s1[i] == s2[j]) {
			return i;
		}
	}

	return -1;
}

int main()
{
	const char s1[] = "int any(const char s1[], const char s2[])";
	const char s2[] = "no";
	const char s3[] = "yes";
	const char s4[] = "boy";
	const char s5[] = "girl";
	const char s6[] = "DEFINE";
	printf("==========\n");
	printf("%s\n", s1);
	printf("==========\n");
	printf("any(s1, \"%s\")=%d\n", s2, any(s1, s2));
	printf("any(s1, \"%s\")=%d\n", s3, any(s1, s3));
	printf("any(s1, \"%s\")=%d\n", s4, any(s1, s4));
	printf("any(s1, \"%s\")=%d\n", s5, any(s1, s5));
	printf("any(s1, \"%s\")=%d\n", s6, any(s1, s6));
	return 0;
}
