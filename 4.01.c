/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 07:18:39 PM CST
 * Modified : Thu 09 Aug 2012 07:19:33 PM CST
 */

/*
 * Write the function ``strindex(s,t)'' which returns the position of the
 * *rightmost* occurrence of ``t'' in ``s'', or ``-1'' if there is none.
 */

int strindex(const char s[], const char t[])
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) ;
	for (i--; i > 0; i--) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
		if (k > 0 && t[k] == '\0') {
			return i;
		}
	}

	return -1;
}

int main()
{
	char s[] = "hello world or C";
	char t[] = "or";
	int pos = strindex(s, t);
	printf("s=%s, t=%s, pos=%d\n", s, t, pos);
	return 0;
}
