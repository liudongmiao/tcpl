/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 08:27:43 PM CST
 * Modified : Mon 13 Aug 2012 03:04:11 PM CST
 */

/*
 * Add the commands to print the top elements of the stack without popping, to
 * duplicate it, and to swap the top two elements. Add a command to clear the
 * stack.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
#ifndef ORIGINAL
void showtop(int n);
void yank(int n);
void swap();
void clear();
#endif

/* reverse Polish calculator */
int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
#ifndef ORIGINAL
			case '%':
				op2 = pop();
				if ((int)op2 != 0)
					push((int)pop() % (int)op2);
				else
					printf("error: zero modulus\n");
				break;
			case '?':
				printf("simple calcator\n");
				printf("\tsupport + - * / %% \n");
				printf("\t?\tshow this help\n");
				printf("\t~[n]\tshow top n elements\n");
				printf("\t&[n]\tduplicate top n elements\n");
				printf("\t^\tswap the top 2 elements\n");
				printf("\t!\tclear the stack\n");
				break;
			case '~':
				showtop(atoi(s + 1));
				break;
			case '&':
				yank(atoi(s + 1));
				break;
			case '^':
				swap();
				break;
			case '!':
				clear();
				break;
#endif
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL 100	/* maximum depth of val stack */
int sp = 0;			/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>
int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
#ifdef ORIGINAL
	if (!isdigit(c) && c != '.')
		return c; 		/* not a number */
	i = 0;
#else
	i = 0;
	/* show[n] */
	if (c == '~') {
		while (isdigit(s[++i] = c = getch()))
			;
		s[i] = '\0';
		return '~';
	}
	/* yank[n] */
	if (c == '&') {
		while (isdigit(s[++i] = c = getch()))
			;
		s[i] = '\0';
		return '&';
	}

	/* handle other commands */
	if (c == '?' || c == '^' || c == '!') {
		i = getch();
		if (i != '\n') {
			ungetch(i);
		}
		return c;
	}
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	if (c == '-') {
		c = getch();
		if (!isdigit(c) && c != '.') {
			ungetch(c);
			return '-';
		}
		s[++i] = c;
	}
#endif
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)		/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
#ifndef ORIGINAL
void showtop(int n)
{
	int i;
	if (n == 0 || n >= sp) {
		n = sp;
	}
	for (i = 1; i <= n; i++) {
		printf("top %02d(%02d): %f\n", i, sp - i, val[sp - i]);
	}
}

void yank(int n)
{
	int i;
	if (n == 0 || n >= sp) {
		n = sp;
	}
	i = sp - n;
	while (n-- > 0) {
		push(val[i++]);
	}
}

void swap()
{
	double s1;
	double s2;
	if (sp > 2) {
		s1 = pop();
		s2 = pop();
		push(s1);
		push(s2);
	} else {
		printf("error: no enough stack\n");
	}
}

void clear(void)
{
	sp = 0;
}
#endif
