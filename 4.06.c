/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Fri 10 Aug 2012 10:26:16 AM CST
 * Modified : Mon 13 Aug 2012 03:04:53 PM CST
 */

/*
 * Add commands for handling variables. (It's easy to provide twenty-six
 * variables with single-letter names.) Add a variable for the most recently
 * printed value.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
#ifndef ORIGINAL
double var[27];
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
				printf("\t= [a-z]\tlet [a-z] = last stack\n");
				printf("\t[a-z]\tuse [a-z]'s value\n");
				printf("\t_\tlast printed value\n");
				break;
			case '=':
				type = getop(s) - 'a';
				if (type < 0 && type >= 26) {
					printf("error: invalid variable\n");
				} else {
					var[type] = pop();
				}
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				push(var[type - 'a']);
				break;
			case '_':
				push(var[26]);
				break;
#endif
			case '\n':
#ifndef ORIGINAL
				var[26] = pop();
				printf("\t%.8g\n", var[26]);
#else
				printf("\t%.8g\n", pop());
#endif
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
	/* handle help command */
	if (c == '?') {
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
