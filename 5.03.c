/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Sat 11 Aug 2012 09:25:58 PM CST
 * Modified : Sat 11 Aug 2012 10:36:58 PM CST
 */

/*
 * Write a pointer version of the function ``strcat'' that we showed in Chapter
 * 2: ``strcat(s,t)'' copies the string ``t'' to the end of ``s''.
 */

char *strcat(char *s, const char *t)
{
	while (*s)
		s++;
	while ((*s++ = *t++))
		;
	return s;
}

#include <stdio.h>
int main()
{
	char s[20] = "hello";
	char t[] = " world!";
	strcat((char *)&s, (char *)&t);
	strcat((char *)&s, (char *)&t);
	printf("s=%s\n", s);
	return 0;
}
