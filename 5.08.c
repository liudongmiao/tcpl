/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Mon 13 Aug 2012 10:58:16 AM CST
 * Modified : Mon 13 Aug 2012 11:09:16 AM CST
 */

/*
 * There is no error checking in ``day_of_year'' or ``month_day''. Remedy this
 * defect.
 */

#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 32, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
#ifdef ORIGINAL
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
#else
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	if (month > 12 || day > daytab[leap][month]) {
		printf("error: invalid month %d and/or day %d\n", month, day);
	}
#endif
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
#ifdef ORIGINAL
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
#else
	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	for (i = 1; i < 13 && yearday > daytab[leap][i]; i++)
#endif
		yearday -= daytab[leap][i];
#ifndef ORIGINAL
	if (yearday <= 0 || yearday > daytab[leap][i]) {
		printf("error: invalid month %d, day %d\n", i, yearday);
	}
#endif
	*pmonth = i;
	*pday = yearday;
}

int main()
{
	int year, month, day, yearday;;
	year = 2012, month = 8, day = 35;
	yearday = day_of_year(year, month, day);
	printf("day_of_year: %d\n", yearday);
	month_day(year, yearday, &month, &day);
	printf("month=%d, day=%d\n", month, day);
	return 0;
}
