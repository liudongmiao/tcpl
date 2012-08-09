/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 08 Aug 2012 02:47:44 PM CST
 * Modified : Thu 09 Aug 2012 10:12:11 AM CST
 */

/*
 * In a two's complement number system, ``x &= (x-1)'' deletes the rightmost
 * 1-bit in ``x''. Explain why. Use this observation to write a faster version
 * of ``bitcount''.
 */

#include <stdio.h>

#ifdef ORIGINAL
/* bitcount: count 1 bits in x*/
int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1) {
		if (x & 01) {
			b++;
		}
	}
	return b;
}

#else
/*
 * if x & 01; x - 1 deletes the 1, i.e. the rightmost 1-bit.
 * if x & 00; x - 1 will borrow 1 from the rightmost 1-bit, then other will be
 * delete, ie the rightmost 1-bit will be deleted.
 */

/* bitcount: count 1 bits in x, fast version*/
int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x &= (x - 1)) {
		b++;
	}
	return b;
}
#endif

#define N 0xabcdef
int main()
{
	int i;

#ifdef ORIGINAL
		printf("original version\n");
#else
		printf("solution version\n");
#endif
	for (i = 0; i < N; i++) {
		bitcount(0xf00dba11);
	}

	return 0;
}
