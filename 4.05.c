/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 10 Aug 2012 10:24:39 AM CST
 * Modified : Mon 13 Aug 2012 03:04:26 PM CST
 */

/*
 * Add access to library functions like ``sin'', ``exp'', and ``pow''. See
 * <math.h> in Appendix B, Section 4.
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef ORIGINAL
#include <math.h>
#define SIN 's'
#define EXP 'e'
#define POW 'p'
#endif

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

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
			case SIN:
				push(sin(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				push(pow(pop(), op2));
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
	/* sin */
	if (c == 's') {
		if ((c = getch()) != 'i') {
			ungetch(c);
		} else if ((c = getch()) != 'n') {
			ungetch(c);
		}
		s[1] = 'i';
		s[2] = 'n';
		s[3] = '\0';
		return SIN;
	}

	/* exp */
	if (c == 'e') {
		if ((c = getch()) != 'x') {
			ungetch(c);
		} else if ((c = getch()) != 'p') {
			ungetch(c);
		}
		s[1] = 'x';
		s[2] = 'p';
		s[3] = '\0';
		return EXP;
	}

	/* pow */
	if (c == 'p') {
		if ((c = getch()) != 'o') {
			ungetch(c);
		} else if ((c = getch()) != 'w') {
			ungetch(c);
		}
		s[1] = 'o';
		s[2] = 'w';
		s[3] = '\0';
		return POW;
	}

	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	i = 0;
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
