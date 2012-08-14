/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Mon 13 Aug 2012 11:13:11 AM CST
 * Modified : Mon 13 Aug 2012 11:32:16 AM CST
 */

/*
 * Rewrite the routines ``day_of_year'' and ``month_day'' with pointers instead
 * of indexing.
 */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 32, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	char *pdaytab;
	if (month < 1 || month > 12) {
		printf("error: invalid month %d\n", month);
	}
	pdaytab = daytab[(year % 4 == 0 && year % 100 != 0) || year % 400 == 0];
	if (day < 1 || day > pdaytab[month]) {
		printf("error: invalid day %d for year %d, month %d\n", day, year, month);
	}
	while (month-- > 0) {
		day += *pdaytab++;
	}
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	char *pdaytab, *pdaytmp;
	pdaytab = daytab[(year % 4 == 0 && year % 100 != 0) || year % 400 == 0];
	pdaytmp = pdaytab;
	while (pdaytmp - pdaytab < 12 && yearday > *pdaytmp) {
		yearday -= *pdaytmp++;
	}
	*pmonth = (pdaytmp - pdaytab);
	*pday = yearday;
}

int main()
{
	int year, month, day, yearday;;
	year = 2012, month = 12, day = 35;
	yearday = day_of_year(year, month, day);
	printf("day_of_year: %d\n", yearday);
	month_day(year, yearday, &month, &day);
	printf("month=%d, day=%d\n", month, day);
	return 0;
}
