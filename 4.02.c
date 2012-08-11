/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 07:39:52 PM CST
 * Modified : Thu 09 Aug 2012 07:52:57 PM CST
 */

/*
 * Extend ``atof'' to handle scientific notation of the form ``123.45e-6'' where
 * a floating-point number may be followed by ``e'' or ``E'' and an optionally
 * signed exponent.
 */

#include <ctype.h>
#ifndef ORIGINAL
double extend_power(char s[], int i)
{
	double power;
	int val, sign = 1;
	if (s[i] == '-') {
		sign = -1;
	} else if (s[i] == '+') {
		sign = 1;
	}

	for (val = 0, i++; isdigit(s[i]); i++) {
		val = 10 * val + (s[i] - '0');
	}

	for (power = 1.0; val > 0; val--) {
		if (sign > 0) {
			power *= 10.0;
		} else {
			power /= 10.0;
		}
	}

	return power;
}
#endif

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++)	/* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
#ifndef ORIGINAL
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		power /= extend_power(s, i);
	}
#endif
	return sign * val / power;
}

#include <stdio.h>
int main()
{
	char s[] = "123.45e-6";
	double d = atof(s);
	printf("s=%s, d=%f\n", s, d);
	return 0;
}
