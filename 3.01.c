/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 10:47:34 AM CST
 * Modified : Thu 09 Aug 2012 03:07:12 PM CST
 */

/*
 * Our binary search makes two tests inside the loop, when one would suffice (at
 * the price of more tests outside.) Write a version with only one test inside
 * the loop and measure the difference in run-time.
 */

#ifdef ORIGINAL
/* XXX: ``high = mid + 1'' should be ``high = mid - 1'', or dead loop */
/* binsearch: find x in v[0] <= v[1] <= ... <= v[n=1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid + 1;
		else if (x > v[mid])
			low = mid + 1;
		else	/* found match */
			return mid;
	}

	return -1;
}

#else
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while (low <= high && x != v[mid]) {
		if (x < v[mid]) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
		mid = (low + high) / 2;
	}

	if (x == v[mid]) {
		return mid;
	}

	return -1;
}
#endif

#include <stdio.h>
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
int main()
{
	int v[] = {1, 2, 3, 5, 8, 13, 21, 33, 54, 87};
	int x;
	int n;

	x = 5;
	n = binsearch(x, v, ARRAY_SIZE(v));
	printf("x=%d, n=%d\n", x, n);

	x = 23;
	n = binsearch(x, v, ARRAY_SIZE(v));
	printf("x=%d, n=%d\n", x, n);

	x = 33;
	n = binsearch(x, v, ARRAY_SIZE(v));
	printf("x=%d, n=%d\n", x, n);

	return 0;
}
