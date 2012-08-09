/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 01:19:04 PM CST
 * Modified : Wed 08 Aug 2012 01:19:31 PM CST
 */

/*
 * Write an alternative version of ``squeeze(s1, s2)'' that deletes each
 * character in ``s1'' that matches any character in the *string* ``s2''.
 */

void squeeze(char s1[], const char s2[])
{
	int i, j, c;

	for (i = j = 0; s1[i] != '\0'; i++) {
		for (c = 0; s1[i] != s2[c] && s2[c] != '\0'; c++) ;
		if (s1[i] != s2[c]) {
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}

int main()
{
	char s1[] = "void squeeze(char s1[], const char s2[])";
	char s2[] = "ce";
	printf("s1=%s\n", s1);
	squeeze(s1, s2);
	printf("s1=%s\n", s1);
	return 0;
}
