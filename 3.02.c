/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 12:39:21 PM CST
 * Modified : Thu 09 Aug 2012 02:08:59 PM CST
 */

/*
 * Write a function ``escape(s, t)'' that converts characters like newline and
 * tab into visible escape sequences like ``\n'' ant ``\t'' as it copies the
 * string ``t'' to ``s''. Use a ``switch''. Write a function for the other
 * direction as well, converting escape sequences into the real characters.
 */

#include <stdio.h>

void escape(char s[], const char t[])
{
	int i, j = 0;
	for (i = 0; t[i] != '\0'; i++) {
		switch (t[i]) {
			case '\a':
				s[j++] = '\\';
				s[j++] = 'a';
				break;
			case '\b':
				s[j++] = '\\';
				s[j++] = 'b';
				break;
			case '\e':
				s[j++] = '\\';
				s[j++] = 'e';
				break;
			case '\f':
				s[j++] = '\\';
				s[j++] = 'f';
				break;
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\r':
				s[j++] = '\\';
				s[j++] = 'r';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			case '\v':
				s[j++] = '\\';
				s[j++] = 'v';
				break;
			case '\\':
				s[j++] = '\\';
				s[j++] = '\\';
				break;
			default:
				s[j++] = t[i];
		}
	}
}

void unescape(char s[], const char t[])
{
	int i, j = 0;
	for (i = 0; t[i] != '\0'; i++) {
		if (t[i] == '\\') {
			switch (t[++i]) {
				case 'a':
					s[j++] = '\a';
					break;
				case 'b':
					s[j++] = '\b';
					break;
				case 'e':
					s[j++] = '\e';
					break;
				case 'f':
					s[j++] = '\f';
					break;
				case 'n':
					s[j++] = '\n';
					break;
				case 'r':
					s[j++] = '\r';
					break;
				case 't':
					s[j++] = '\t';
					break;
				case 'v':
					s[j++] = '\v';
					break;
				case '\\':
					s[j++] = '\\';
					break;
				default:
					printf("invalid %c(0x%02x)", t[i], t[i]);
			}
		} else {
			s[j++] = t[i];
		}
	}
}

int strcmp(const char s[], const char t[])
{
	int i;

	for (i = 0; ; i++) {
		if (s[i] != t[i]) {
			return -1;
		} else if (s[i] == '\0') {
			return 0;
		}
	}

	return -1;
}

int main()
{
	char s[] = "\\\a\bcd\e\fghijklm\nopq\rs\tu\vwxyz";
	char t[52] = {0};
	char u[52] = {0};
	escape(t, s);
	printf("t=%s\n", t);
	unescape(u, t);
	printf("s%su\n", strcmp(s, u) == 0 ? "=" : "!=");
	return 0;
}
