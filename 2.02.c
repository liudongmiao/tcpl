/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 10:59:04 AM CST
 * Modified : Thu 09 Aug 2012 09:36:54 AM CST
 */

/*
 * Write a loop equivalent to the ``for'' loop above without using ``&&'' or
 * ``||''.
 *
 * for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 * 	s[i] = c;
 */

#include <stdio.h>
int main()
{
	int i, c, lim = 2048;
	char s[lim];

	/*
	for (i = 0; i < lim - 1; ++i) {
		c = getchar();
		if (c == '\n') {
			i = lim - 1;
		}
		if (c == EOF) {
			i = lim - 1;
		}
		s[i] = c;
	}
	*/
	for (i=0; i < lim-1 ? ((c=getchar()) != '\n' ? c != EOF : 0) : 0; ++i)
		s[i] = c;

	printf("%s\n", s);
	return 0;
}
