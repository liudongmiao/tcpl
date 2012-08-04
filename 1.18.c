/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 27 Jul 2012 07:25:20 PM CST
 * Modified : Sat 04 Aug 2012 09:34:25 PM CST
 */

/*
 * Write a program to remove trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines.
 */

#include <stdio.h>
#define LENGTH 1024

int main()
{
	int c, i = 0, j = 0, k;
	char line[LENGTH];
	char blank[LENGTH];
	line[i] = '\0';
	blank[j] = '\0';
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			if (i != 0) {
				line[i] = '\0';
				printf("line=%s\n", line);
			}
			i = j = 0;
			line[i] = '\0';
		} else  if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r') {
			blank[j] = c;
			j++;
		} else {
			// copy blank to line
			for (k = 0; k < j; k++, i++) {
				line[i] = blank[k];
			}
			line[i] = c;
			i++;
			j = 0;
		}
	}
	return 0;
}
